
PROJECT_DIR = $(shell dirname $(shell dirname $(PWD)))
NVCC = nvcc
CXXFLAGS = -std=c++14
CUBLAS = /usr/local/cuda-10.1/man/man7/libcublas.so.7 #Have to make sure the libcublas.so.7 file is here, otherwise provide the proper path
OPENCV_LIB_FLAGS = $(shell pkg-config --cflags --libs opencv)
PROTOBUF_LIB_FLAGS = $(shell pkg-config --libs protobuf) 
CUDA_LIB_FLAGS = -lcudnn -lcublas -lcufft -arch=sm_35 -rdc=true -O3
OPERATIONS_LIBRARY = $(shell find $(PROJECT_DIR) -name operations.cc)
CNN_FORWARD_LIBRARY = $(shell find $(PROJECT_DIR) -name cnn_forward.cc)
DATA_UTIL_LIBRARY = $(shell find $(PROJECT_DIR) -name data_util.cc)
TRANSLATOR_LIBRARY = $(shell find $(PROJECT_DIR) -name translator.cc)
PROTO_LIBRARY = $(shell find $(PROJECT_DIR) -name network.pb.cc)
DIRECT_CONV = $(shell find $(PROJECT_DIR) -name direct_conv.cu)
FFT_FILE = fft_fast.cu
FFT_KERNEL = $(shell find $(PROJECT_DIR) -name $(FFT_FILE))
WINOGRAD_FILE = winograd_fast.cu
WINOGRAD_KERNEL = $(shell find $(PROJECT_DIR) -name $(WINOGRAD_FILE))
IM2COL_KERNEL = $(shell find $(PROJECT_DIR) -name im2col.cu)


.PHONY : all clean

all : test

test: batch_test.cc $(OPERATIONS_LIBRARY) $(CNN_FORWARD_LIBRARY) $(DATA_UTIL_LIBRARY) $(TRANSLATOR_LIBRARY) $(PROTO_LIBRARY) $(FFT_KERNEL) $(DIRECT_CONV) $(WINOGRAD_KERNEL) $(IM2COL_KERNEL)
	$(NVCC) -I $(PROJECT_DIR) -L $(CUBLAS) $(CXXFLAGS) $^ $(OPENCV_LIB_FLAGS) $(PROTOBUF_LIB_FLAGS) $(CUDA_LIB_FLAGS) -o $@

clean:
	rm -f test
	rm -f *.txt

run_cudnn:
	./test "$(PROJECT_DIR)/pretrained-models/vgg19.pb" 1>/dev/null
	python batch_test.py vgg
	@echo ""
	./test "$(PROJECT_DIR)/pretrained-models/alexnet.pb" 1>/dev/null
	python batch_test.py alex 

run_direct:
	./test "$(PROJECT_DIR)/pretrained-models/vgg19.pb" "DIRECT" 1>/dev/null
	python batch_test.py vgg
	@echo ""
	./test "$(PROJECT_DIR)/pretrained-models/alexnet.pb" "DIRECT" 1>/dev/null
	python batch_test.py alex 

run_fft:
	./test "$(PROJECT_DIR)/pretrained-models/vgg19.pb" "FFT" 1>/dev/null
	python batch_test.py vgg
	@echo ""
	./test "$(PROJECT_DIR)/pretrained-models/alexnet.pb" "FFT" 1>/dev/null
	python batch_test.py alex
	
run_winograd:
	./test "$(PROJECT_DIR)/pretrained-models/vgg19.pb" "WINOGRAD" 1>/dev/null
	python batch_test.py vgg

run_im2col:
	./test "$(PROJECT_DIR)/pretrained-models/vgg19.pb" "IM2COL" 1>/dev/null
	python batch_test.py vgg
	@echo ""
	./test "$(PROJECT_DIR)/pretrained-models/alexnet.pb" "IM2COL" 1>/dev/null
	python batch_test.py alex 


