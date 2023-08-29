/*
 * socket_client.h
 *
 *  Created on: Aug 27, 2023
 *      Author: nhat.tranminh
 */

#ifndef NETWORK_SOCKET_CLIENT_H_
#define NETWORK_SOCKET_CLIENT_H_

#include "stdint.h"
#include "string.h"


#define MESSAGE_MAX_LENGTH 		(2048U)
#define WRITE_CHUNK_SIZE		(1024U)
#define READ_CHUNK_SIZE			WRITE_CHUNK_SIZE
typedef enum {
	CREATE_SOCKET = 0,
	CONNECT_SOCKET,
	SEND_MSG_SOCKET,
	RECEIVE_MSG_SOCKET,
	HANDLE_MSG_SOCKET,
	CLOSE_SOCKET,
	RECREATE_SOCKET
}socket_state;

typedef struct msg_t{
	char msg[MESSAGE_MAX_LENGTH];
	uint32_t index;
	size_t len;
}msg_t;

typedef struct socket_t{
	int sockfd;
	msg_t sock_tx_msg;
	msg_t sock_rx_msg;
}socket_t;

#define SOCK_CONNECT_OK_BIT		(0x01 << 0)
#define SOCK_CONNECT_FAIL_BIT	(0x01 << 1)


void WriteLWIPClientTask(void const *argument);
void ReadLWIPClientTask(void const *argument);

#endif /* NETWORK_SOCKET_CLIENT_H_ */
