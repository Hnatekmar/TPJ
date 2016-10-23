default:
	make -C project

test:
	make -C tests clean
	make -C tests
