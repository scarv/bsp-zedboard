#!/usr/bin/python3

"""
A python3 script for uploading binaries to the Zeboard and running them
on the RISC-V core.
"""

import sys
import argparse
import logging as log

import serial

def parse_args():
    """
    Responsible for parsing all arguments to the flow script.
    """
    parser = argparse.ArgumentParser()

    parser.add_argument("--port", type=str, default="/dev/ttyACM0",
        help="Which serial port used to communicate with the target.")
    
    parser.add_argument("--baud", type=int, default=115200,
        help="Baud rate to communicate with the target at.")
    
    parser.add_argument("--timeout", type=int, default=3,
        help="Timeout after this many seconds trying to communicate.")

    parser.add_argument("file", type=argparse.FileType("rb"),
        help="The file to send to the target")


    return parser.parse_args()


def main():
    """
    Main function for the script
    """

    args    = parse_args()

    port    = serial.Serial()
    port.baudrate = args.baud
    port.port     = args.port
    port.timeout  = args.timeout

    port.open()

    if(port.is_open):
        log.info("Openned port %s at baud %d" % (port.port,port.baudrate))
    else:
        log.error("Failed to open port %s at baud %d" % (
            port.port,port.baudrate))
        sys.exit(1)

    while(port.in_waiting):
        rdata = port.read(1).decode("ascii")
        sys.stdout.write(rdata)
    sys.stdout.flush()
    
    data_tosend = args.file.read()
    data_length = len(data_tosend).to_bytes(4, byteorder='big')
    
    sent = 0
    print("-- Sending %d bytes to %s" % (len(data_tosend),port.port))
    sent += port.write(bytes([1]))
    sent += port.write(data_length)
    sent += port.write(data_tosend)
    
    print("-- Sent %d bytes in total" % sent)
    print("-- CTRL-C to exit.")

    try:
        sys.stdout.write(">> ");
        while(True):
            rdata = port.read(1).decode("ascii")
            if(rdata == "\n"):
                sys.stdout.write("\n>> ")
            else:
                sys.stdout.write(rdata)
        sys.stdout.flush()
    except KeyboardInterrupt:
        print()
        pass

    port.close()

    sys.exit(0)


if(__name__ == "__main__"):
    main()
