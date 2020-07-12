#include <stdio.h>
#include <stdlib.h>

void main() {

  FILE * read;
  read = fopen( "mmd_data.txt", "r" );
  FILE * fp;
  fp = fopen( "buffer.vhd", "w" );

  int counter;
  int port = 1;
  char port_addr[25] = "0001 0010 0011 0100 0101";
  port_addr[4] = '\0';
  port_addr[9] = '\0';
  port_addr[14] = '\0';
  port_addr[19] = '\0';
  port_addr[24] = '\0';

  char rw;
  char buf_mmd[5], buf_reg[5], buf_data[7];
  long int mmd, reg, data;

  fprintf( fp, "SIGNAL tx_buffer      : tx_array :=\n(\n" );

  printf( "How many lines of input?\n" );
  scanf( "%d", &counter );
  printf( "Translating %d lines...\n", counter );
  while( counter ) {
    if( counter ) port = 1;
    fscanf( read, "%c %s %s %s\n", &rw, buf_mmd, buf_reg, buf_data );

    mmd = strtol( buf_mmd, NULL, 16 );
    reg = strtol( buf_reg, NULL, 16 );
    data = strtol( buf_data, NULL, 16 );

    printf( "%s\n", rw == 'w' ? "Write" : "Read" );
    printf( "%02X\t%02X\t%04X\n", (unsigned int)mmd, (unsigned int)reg, (unsigned int)data );

    while( port < 6 ) {
      fprintf( fp, "\n" );
      fprintf( fp, "\t\"01000000000%s0001000110100010000000000", &port_addr[(port-1)*5] );
      for( int i = 7; i >= 0; i-- ) {
        int bit = mmd >> i;
        if( bit & 1 )
          fprintf( fp, "1" );
        else
          fprintf( fp, "0" );
      }
      fprintf( fp, "\",\n" );

      fprintf( fp, "\t\"01000000000%s0001000111000010000000000", &port_addr[(port-1)*5] );
      for( int i = 7; i >= 0; i-- ) {
        int bit = reg >> i;
        if( bit & 1 )
          fprintf( fp, "1" );
        else
          fprintf( fp, "0" );
      }
      fprintf( fp, "\",\n" );

      fprintf( fp, "\t\"01000000000%s0001000110100010001000000", &port_addr[(port-1)*5] );
      for( int i = 7; i >= 0; i-- ) {
        int bit = mmd >> i;
        if( bit & 1 )
          fprintf( fp, "1" );
        else
          fprintf( fp, "0" );
      }
      fprintf( fp, "\",\n" );

      fprintf( fp, "\t\"01000000000%s00010001110000100", &port_addr[(port-1)*5] );
      for( int i = 15; i >= 0; i-- ) {
        int bit = data >> i;
        if( bit & 1 )
          fprintf( fp, "1" );
        else
          fprintf( fp, "0" );
      }
      fprintf( fp, "\"," );

      port++;
    }
    counter--;
  }

  fprintf( fp, "\n\n);" );
  fclose( fp );

}
