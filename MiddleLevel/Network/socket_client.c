/*
 * socket_client.c
 *
 *  Created on: Aug 27, 2023
 *      Author: nhat.tranminh
 */

#include "socket_client.h"
#include "sockets.h"
#include "inet.h"
#include "test_data.h"
#include "dbg.h"
#include "lwip.h"
#include "stdbool.h"

//Define Server IP
#define ETH_SERVER_IP		"192.168.0.105"
#define ETH_SERVER_PORT		23

bool is_sock_connect = false;

void WriteLWIPClientTask(void const *argument)
{
	struct sockaddr_in addr = {
		.sin_len = sizeof(addr),
		.sin_family = AF_INET,
		.sin_port = PP_HTONS(ETH_SERVER_PORT),
		.sin_addr.s_addr = inet_addr(ETH_SERVER_IP),
	};
	socket_t gsocket;
	memset(&gsocket, 0, sizeof(gsocket));

	socket_state sockState = CREATE_SOCKET;
	int ret = ERR_OK;
	while(1)
	{
		switch(sockState)
		{
			case CREATE_SOCKET:
			{
				memset(&gsocket, 0, sizeof(gsocket));
				gsocket.sockfd = lwip_socket(AF_INET, SOCK_STREAM, 6);
				if(gsocket.sockfd == -1){
					DB_ERR_PRINTF("\r\n**Failed to create the socket**\r\n");
					sockState = RECREATE_SOCKET;
					osDelay(5000);
				}else{
					DB_PRINTF("\r\nCreate the socket successfully\r\n");
					sockState = CONNECT_SOCKET;
				}
				break;
			}
			case CONNECT_SOCKET:
			{
				ret = lwip_connect(gsocket.sockfd, (const struct sockaddr*)&addr, sizeof(addr));
				if(ret != ERR_OK){
					DB_ERR_PRINTF("\r\n**Failed to connect to socket server**\r\n");
					sockState = RECREATE_SOCKET;
					is_sock_connect = false;
				}else{
					DB_PRINTF("\r\nConnect to socket server successfully\r\n");
					sockState = SEND_MSG_SOCKET;
					is_sock_connect = true;
					osStatus queue_ret = osMessagePut(sockfd_queueHandle, gsocket.sockfd, 0);
					if(queue_ret != osOK){
						DB_PRINTF("\r\nFailed to send queue\r\n");
					}
				}
				break;
			}
			case SEND_MSG_SOCKET:
			{
				memset(gsocket.sock_tx_msg.msg, 0, sizeof(gsocket.sock_tx_msg.msg));
#ifdef USE_DATA_1KB
				gsocket.sock_tx_msg.len = strlen(data_1kb);
#elif USE_DATA_2KB
				gsocket.sock_tx_msg.len = strlen(data_2kb);
#elif USE_DATA_10KB
				gsocket.sock_tx_msg.len = strlen(data_10kb);
#endif
				gsocket.sock_tx_msg.index = 0;
				unsigned int sizeLeft = gsocket.sock_tx_msg.len;
				unsigned int sizeWrite = 0;
				while(sizeLeft > 0)
				{
					sizeWrite = (sizeLeft > WRITE_CHUNK_SIZE) ? (WRITE_CHUNK_SIZE) : sizeLeft;

#ifdef USE_DATA_1KB
					char * write_buf = stringCpy(data_1kb, gsocket.sock_tx_msg.index, gsocket.sock_tx_msg.index + sizeWrite - 1);
#elif USE_DATA_2KB
					char * write_buf = stringCpy(data_2kb, gsocket.sock_tx_msg.index, gsocket.sock_tx_msg.index + sizeWrite - 1);
#else USE_DATA_10KB
					char * write_buf = stringCpy(data_10kb, gsocket.sock_tx_msg.index, gsocket.sock_tx_msg.index + sizeWrite - 1);
#endif
					strcpy(gsocket.sock_tx_msg.msg, write_buf);
					ret = lwip_write(gsocket.sockfd, gsocket.sock_tx_msg.msg, sizeWrite);
					if(ret == -1){
						DB_ERR_PRINTF("\r\n**Failed to send message to socket server**\r\n");
						sockState = CONNECT_SOCKET;
						break;
					}else{
						DB_PRINTF("\r\nSend message to socket successfully\r\n");
						sockState = SEND_MSG_SOCKET;
					}

					gsocket.sock_tx_msg.index += (sizeWrite);
					sizeLeft = sizeLeft - sizeWrite;
					memset(gsocket.sock_tx_msg.msg, 0, sizeof(gsocket.sock_tx_msg.msg));
					free(write_buf);
				}
				osDelay(5000);
				break;
			}
			case CLOSE_SOCKET:
			{
				ret = lwip_close(gsocket.sockfd);
				if(ret != ERR_OK){
					DB_PRINTF("\r\n**Failed to close the socket**\r\n");
					sockState = CLOSE_SOCKET;
				}else{
					is_sock_connect = false;
					goto exit;
				}
				break;
			}
			case RECREATE_SOCKET:
			{
				ret = lwip_close(gsocket.sockfd);
				if(ret != ERR_OK){
					DB_PRINTF("\r\n**Failed to close the socket**\r\n");
					sockState = RECREATE_SOCKET;
				}else{
					is_sock_connect = false;
					sockState = CREATE_SOCKET;
				}
				break;
			}
			default:
				break;
		}
	}
	exit:
	vTaskDelete(NULL);
}


void ReadLWIPClientTask(void const *argument)
{
	socket_t gsocket;
	memset(&gsocket, 0, sizeof(gsocket));
	while(1)
	{
		//Waiting for connection
		osEvent queue_event = osMessageGet(sockfd_queueHandle, osWaitForever);
		gsocket.sockfd = queue_event.value.v;
		gsocket.sock_rx_msg.len = sizeof(gsocket.sock_rx_msg.msg);
		while(is_sock_connect){
			ssize_t read_len = lwip_read(gsocket.sockfd, gsocket.sock_rx_msg.msg, gsocket.sock_rx_msg.len);
			if(read_len != -1){
				DB_PRINTF("\r\nData received from server: \r\n%s\r\n", gsocket.sock_rx_msg.msg);
			}
			memset(gsocket.sock_rx_msg.msg, 0, sizeof(gsocket.sock_rx_msg.msg));
			osDelay(100);
		}
	}
}
