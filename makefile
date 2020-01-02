DIR_SUBS = src tests

all:
	@for subdir in ${DIR_SUBS}; do \
		$(MAKE) -C $$subdir; \
		done

install:clean all
	cp src/libcore.a build

clean:
	@for subdir in ${DIR_SUBS}; do \
		$(MAKE) clean -C $$subdir; \
		done
	rm -rf build/*
