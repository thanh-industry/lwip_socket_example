import socket
import threading
import tkinter as tk
from tkinter import ttk

class Form1(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title("TCP Socket Server")
        self.geometry("700x700")

        self.LISTEN_PORT = 80
        self.server = None
        self.server_thread = None
        self.connection_count = 0
        self.client_threads = {}
        self.message_counts = {}  # Dictionary to store message counts for each client

        self.lbx_message = tk.Listbox(self)
        self.lbx_message.pack(fill=tk.BOTH, expand=True)

        self.info_label = tk.Label(self, text="Client Info:")
        self.info_label.pack(fill=tk.X)

        self.data_text = tk.Text(self, wrap=tk.WORD)
        self.data_text.pack(fill=tk.BOTH, expand=True)
        
        self.message_entry_label = tk.Label(self, text="Message:")
        self.message_entry_label.pack(fill=tk.X, padx=10, pady=5)
        
        self.message_entry = tk.Entry(self)
        self.message_entry.pack(fill=tk.X, padx=10, pady=5)

        btn_start = ttk.Button(self, text="Start", command=self.start_server)
        btn_start.pack(side=tk.LEFT, padx=10, pady=5)
        
        btn_send = ttk.Button(self, text="Send", command=self.send_message)
        btn_send.pack(side=tk.LEFT, padx=10, pady=5)

        btn_clear_listbox = ttk.Button(self, text="Clear Listbox", command=self.clear_listbox)
        btn_clear_listbox.pack(side=tk.LEFT, padx=10, pady=5)

        btn_clear_data = ttk.Button(self, text="Clear Data", command=self.clear_data_text)
        btn_clear_data.pack(side=tk.LEFT, padx=10, pady=5)

        self.protocol("WM_DELETE_WINDOW", self.on_closing)

    def add_listbox(self, text):
        self.lbx_message.insert(tk.END, text)
        self.lbx_message.see(tk.END)

    def update_info_label(self, text):
        self.info_label.config(text=text)

    def append_data_text(self, text):
        self.data_text.insert(tk.END, text)
        self.data_text.see(tk.END)

    def start_server(self):
        self.server_thread = threading.Thread(target=self.run_server)
        self.server_thread.daemon = True
        self.server_thread.start()

    def run_server(self):
        try:
            self.connection_count = 0
            self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            self.server.bind(("192.168.1.11", self.LISTEN_PORT))
            self.server.listen(5)

            self.add_listbox(f"Server started to listen at port {self.LISTEN_PORT}")

            while True:
                client_socket, client_address = self.server.accept()
                self.connection_count += 1
                self.add_listbox(f"{self.connection_count}: Client accepted...")

                self.client_threads[client_socket] = threading.Thread(target=self.handle_client, args=(client_socket,))
                self.client_threads[client_socket].daemon = True
                self.client_threads[client_socket].start()
                self.message_counts[client_socket] = 0

        except Exception as ex:
            print(ex)

    def send_message(self):
        message = self.message_entry.get()
        if not message:
            return

        for client_socket in self.client_threads.keys():
            try:
                client_socket.send(message.encode("utf-8"))
                client_info = f"{client_socket.getpeername()[0]}:{client_socket.getpeername()[1]}"
                self.add_listbox(f"Server's message: {message} (sent to {client_info})")
            except Exception as ex:
                print(ex)
        self.message_entry.delete(0, tk.END)

    def handle_client(self, client_socket):
        try:
            client_info = f"{client_socket.getpeername()[0]}:{client_socket.getpeername()[1]}"
            self.update_info_label("Client Info: " + client_info)

            while True:
                data = client_socket.recv(4096)
                if not data:
                    break  # Connection closed by client

                self.message_counts[client_socket] += 1
                self.add_listbox(f"{client_info}: Received message {self.message_counts[client_socket]}")

                data_size = len(data)
                self.add_listbox(f"{client_info}: Received message {self.message_counts[client_socket]} of {data_size} bytes")


                data_str = data.decode("utf-8", errors="ignore")
                self.append_data_text(data_str)

        except Exception as ex:
            print(ex)
        finally:
            client_socket.close()
            self.add_listbox(f"{client_info}: Client disconnected")

    def on_closing(self):
        if self.server is not None:
            self.server.close()
        self.destroy()

    def clear_listbox(self):
        self.lbx_message.delete(0, tk.END)

    def clear_data_text(self):
        self.data_text.delete("1.0", tk.END)

if __name__ == "__main__":
    app = Form1()
    app.mainloop()
