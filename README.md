# Index and Search Strategy for Multimodal Search on Navigable Proximity Graph
This repository contains a unified pipeline with seven fine-grained components for performing graph-based ANNS algorithms. Given a graph-based ANNS algorithms (such as [NSG](https://github.com/ZJULearning/nsg), [HNSW](https://github.com/nmslib/hnswlib)), we can break it down to seven fine-grained components according to this framework, and run it through the [CGraph](https://github.com/ChunelFeng/CGraph)'s scheduling. Interestingly, we can obtain a better algorithm quickly by combining the existing algorithms' best-performing components, even without designing a new component. Of course, we can also optimize the components to further improve the algorithm's performance.

## Background

Approximate Nearest Neighbor Search(ANNS) is a task that finds the approximate nearest neighbors among a high-dimensional dataset for a query via a well-designed index. According to the index adopted, the existing ANNS algorithms can be divided into four major types: hashing-based; tree-based; quantization-based; and graph-based algorithms. Recently, graph-based algorithms have emerged as a highly effective option for ANNS. Thanks to graph-based ANNS algorithms' extraordinary ability to express neighbor relationships, they only need to evaluate fewer points of dataset to receive more accurate results, comparing to other categories.

## Install

This project supports MacOS, Linux, and Windows platforms, requiring [CGraph](https://github.com/ChunelFeng/CGraph). You can download this project by running the following instructions.

```
git clone --recursive git@github.com:whenever5225/GraphANNS.git
```

If you are a developer using CLion as the IDE, you can open the `CMakeLists.txt` file as a project for compiling. 

## Usage
You need to configure the data file, index file, and parameters in [here](https://github.com/whenever5225/GraphANNS/blob/main/src/graph_anns_define.h) (please refer to [here](http://corpus-texmex.irisa.fr/) for test data download). Suppose you use 'npg' algorithm and '[siftsmall](ftp://ftp.irisa.fr/local/texmex/corpus/siftsmall.tar.gz)' dataset, you can modify the data path to yours in its configure file (`graph_anns_define.h`):

```cpp
const static char* GA_ALG_BASE_PATH = "your_base_data_root_path/siftsmall/siftsmall_base.fvecs";
const static char* GA_ALG_QUERY_PATH = "your_base_data_root_path/siftsmall/siftsmall_query.fvecs";
const static char* GA_ALG_GROUND_TRUTH_PATH_ = "your_base_data_root_path/siftsmall/siftsmall_groundtruth.ivecs";
const static char* GA_ALG_INDEX_PATH_ = "your_base_data_root_path/anns.index";

const static unsigned GA_NPG_L_CANDIDATE = 100;      // size of candidate set for neighbor selection
const static unsigned GA_NPG_R_NEIGHBOR = 100;       // size of neighbor set
const static unsigned GA_NPG_C_NEIGHBOR = 200;       // number of visited candidate neighbors when neighbor selection
const static unsigned GA_NPG_K_INIT_GRAPH = 20;      // number of neighbors of initial graph
```

HINT: Please refer [here](http://corpus-texmex.irisa.fr/) for the description of `fvecs/ivecs` format.
