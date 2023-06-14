makeall: 
	g++ crc_tx.cpp -g -o crc_tx
	g++ crc_rx.cpp -g -o crc_rx
	g++ crc_vs_parity2d.cpp -o crc_vs_parity2d
	./crc_tx
	./crc_rx
	./crc_vs_parity2d
