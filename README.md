# About
This program is the implementation of the IPv4 checksum (internet checksum).

The IPv4 checksum is a 16-bit checksum used to protect the header of IPv4 data packets against data corruption.
It is done by computing the 16 bit 1's complement of the 1's complement sum of all the 16 bit words in the header packet.

### The IPv4 algorithm: (example from http://www.netfor2.com/checksum.html)

1. Example Packet: 01 00 F2 03 F4 F5 F6 F7 00 00
(00 00 is the checksum field)

2. Form the 16-bit words:
0100 F203 F4F5 F6F7

3. Calculate the 2's complement sum:
0100 + F203 + F4F5 + F6F7 = 0002 DEEF

4. Add the carries (0002) to get the 16-bit 1's complement sum
DEEF + 002 = DEF1

5. Calculate 1's complement of the 1's complement sum
~DEF1 = 210E

6. We send the packet including the checksum 21 0E
01 00 F2 03 F4 F5 F6 F7 21 0E

7. At the receiving end
0100 + F203 + F4F5 + F6F7 + 210E = 0002 FFFD
FFFD + 0002 = FFFF

8. The IPv4 checksum should be 0xFFFF if the data is not corrupted
