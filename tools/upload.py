#!/usr/bin/python3

"""
A python3 script for uploading binaries to the Zeboard and running them
on the RISC-V core.
"""

import sys
import argparse
import logging as log

import serial

CMD_UPLOAD      = bytes([0x1])
CMD_SET_RESET   = bytes([0x2])
CMD_CLR_RESET   = bytes([0x3])
CMD_READ_BUF    = bytes([0x4])

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
    
    subs = parser.add_subparsers(help="What do do.", dest="cmd")


    p_upload = subs.add_parser("upload",help="Upload a new program for the RISC-V core.")
    p_upload.add_argument("file", type=argparse.FileType("rb"),
        help="The file to send to the target")
    p_upload.add_argument("--stdout", action="store_true", 
        help="After uploading, leave the port open and print whatever we recieve")

    p_reset = subs.add_parser("read-buffer",
        help="Read the shared memory buffer from the RISC-V core.")

    p_stdout = subs.add_parser("stdout",
        help="Continually print STDOUT from the RISC-V core to the terminal")

    p_reset = subs.add_parser("set-reset",
        help="Put the RISC-V core in reset")

    p_clear_reset = subs.add_parser("clear-reset",
        help="Take the RISC-V core out of reset and let it run whatever program you have uploaded.")
    p_clear_reset.add_argument("--stdout", action="store_true", 
        help="After clearing reset, leave the port open and print whatever we recieve")

    return parser.parse_args()


def upload(args,port):
    """
    Upload a new binary blob, which is hopefully a program, to the
    RISC-V shared memory.
    """
    data_tosend = args.file.read()
    data_length = len(data_tosend).to_bytes(4, byteorder='big')
    
    sent = 0
    print("-- Sending %d bytes to %s" % (len(data_tosend),port.port))
    sent += port.write(CMD_UPLOAD)
    sent += port.write(data_length)
    sent += port.write(data_tosend)
    
    print("-- Sent %d bytes in total" % sent)

    if(args.stdout):
        read_stdout(args,port)
    else:
        port.close()
        sys.exit(0)


def read_stdout(args,port):
    """
    Read the standard output of the RISC-V core.
    """
    print("-- Reading STDOUT from RISC-V core.")
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


def read_buffer(args,port):
    """
    Read the shared memory buffer from the RISC-V core. Acts like
    a virtual UART.
    """
    print("-- Reading shared memory buffer")
    port.write(CMD_READ_BUF)
    read_stdout(args,port)


def reset(args,port,r):
    """
    Put the RISC-V core into reset (r=True) or take it out of reset (r=False)
    """

    if(r):
        print("-- Putting core into reset.")
        port.write(CMD_SET_RESET)
        print(">> " + port.readline().decode("ascii"))

    else:
        print("-- Clearing core reset.")
        port.write(CMD_CLR_RESET)
        print(">> " + port.readline().decode("ascii"))

        if(args.stdout):
            read_stdout(args,port)

    port.close()
    sys.exit(0)


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
        log.info("Opened port %s at baud %d" % (port.port,port.baudrate))
    else:
        log.error("Failed to open port %s at baud %d" % (
            port.port,port.baudrate))
        sys.exit(1)

    if(args.cmd == "upload"):
        upload(args,port)

    elif(args.cmd == "stdout"):
        read_stdout(args,port)

    elif(args.cmd == "set-reset"):
        reset(args,port, True)

    elif(args.cmd == "clear-reset"):
        reset(args,port, False)
    
    elif(args.cmd == "read-buffer"):
        read_buffer(args,port)

    else:
        log.error("Unknown command: %s" % args.cmd)
        port.close(0)
        sys.exit(1)


if(__name__ == "__main__"):
    main()
