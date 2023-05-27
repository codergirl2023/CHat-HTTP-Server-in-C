Here's a revised version of the README file for the chat application project:

# Chat-HTTP-Server-in-C

This project provides a simple chat application using a client-server model implemented in C. Follow the steps below to set up and run the application.

## Setup

1. If you want to chat on the same PC, open two terminals on that PC. If you want to chat between different PCs, open terminals on each respective PC.

2. Compile the server file on the Server computer:

   ```shell
   gcc Server.c -o Server
   ```

3. Compile the client file on the Client computer:

   ```shell
   gcc Client.c -o Client
   ```

## Running the Application

### On the Server computer:

1. Run the server:

   ```shell
   ./Server <port-no>
   ```

   Replace `<port-no>` with any number greater than 1024 to specify the port on which the server will listen for incoming connections.

### On the Client computer:

1. Run the client:

   ```shell
   ./Client <address> <port-no>
   ```

   - If you want to chat between two PCs on a network, replace `<address>` with the IP address of the Server computer.
   - If you want to chat on the same PC, use the loopback address `127.0.0.1` for `<address>`.
   - Use the same `<port-no>` that you specified while running the server.

2. Start the chat by sending the first message from the client system. You will see the same message on the Server machine.

Please note that this chat application assumes a basic client-server model and does not provide any encryption or authentication mechanisms. 
Feel free to modify and enhance the application to suit your specific requirements.
