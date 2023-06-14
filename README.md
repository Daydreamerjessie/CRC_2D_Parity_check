# CRC_2D_Parity_check
EE450 first project
Ubuntu22.04
I Calculate the CRC and parity code of the given data and printout the generated codeword, corresponding CRC bits and parity bits. Then I check whether the given data can pass these 2 check at the receiver side and print out the result.

crc_tx.cpp: Calculate the CRC for each data and generate codeword and corresponding CRC bits;

crc_rx.cpp: Calculate the remainder of the data with given generator and check whether they pass the crc check, and then printout the result; 

crc_vs_parity2d.cpp: Calculate the CRC and Parity2D for each data, and printout whether they pass these 2 kinds of check.
