install:
	sudo install sh/disbin32.sh /usr/bin/disbin32
	sudo install sh/disbin64.sh /usr/bin/disbin64
	sudo ln -sf /usr/bin/disbin64 /usr/bin/disbin
