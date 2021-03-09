#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "socket.h"

#define BUFFER_LEN 256

int main(int argc, char **argv)
{
  if (argc != 3)
  {
    fprintf(stderr, "Usage: %s <server name> <port>\n", argv[0]);
    exit(1);
  }

  // Read command line arguments
  char *server_name = argv[1];
  unsigned short port = atoi(argv[2]);

  // Connect to the server
  int socket_fd = socket_connect(server_name, port);
  if (socket_fd == -1)
  {
    perror("Failed to connect");
    exit(2);
  }

  // Set up file streams
  // when the client looks like to
  FILE *to_server = fdopen(dup(socket_fd), "wb");
  if (to_server == NULL)
  {
    perror("Failed to open stream to server");
    exit(2);
  }

  FILE *from_server = fdopen(dup(socket_fd), "rb");
  if (from_server == NULL)
  {
    perror("Failed to open stream from server");
    exit(2);
  }

  /*
  client: 
  Declare a message variable string
  While (message != 'quit") {
    // Write to the server 
    fprintf(..., message);
    // wait for server response 
    // server responds, print out
    
  }

  server: 
  while (message != quit) {
    keep sending back what you receive 
  }
  */
  // Read a message from the server
  char buffer[BUFFER_LEN] = "";
  /*
  if (fgets(buffer, BUFFER_LEN, from_server) == NULL)
  {
    perror("Reading from server failed");
    exit(2);
  }
  */
  char line[256];
  while (fgets(line, sizeof line, stdin) != NULL)
  {
    if (strcmp(line, "quit\n") == 0)
    {
      fprintf(to_server, line);
      fflush(to_server);
      break;
    }
    // Send it to the server
    fprintf(to_server, line);
    fflush(to_server);
    // Reading what is from the server
    fgets(buffer, BUFFER_LEN, from_server);
    // Print the message sent back from server
    printf("Server: %s", buffer);
  }

  //printf("Server sent: %s\n", buffer);

  // Send a message to the server
  // it looks like the
  //fprintf(to_server, "Hello server!\n");

  // Flush the output buffer
  //fflush(to_server);

  // Close file streams
  fclose(to_server);
  fclose(from_server);

  // Close socket
  close(socket_fd);

  return 0;
}
