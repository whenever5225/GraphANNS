# GraphANNS: Graph-based Approximate Nearest Neighbor Search Working off CGraph
This repository contains a unified pipeline with seven fine-grained components for performing graph-based ANNS algorithms. Given a graph-based ANNS algorithms (such as [NSG](https://github.com/ZJULearning/nsg), [HNSW](https://github.com/nmslib/hnswlib)), we can break it down to seven fine-grained components according to this framework, and run it through the [CGraph](https://github.com/ChunelFeng/CGraph)'s scheduling. Interestingly, we can obtain a better algorithm quickly by combining the existing algorithms' best-performing components, even without designing a new component. Of course, we can also optimize the components to further improve the algorithm's performance.

## Background

Approximate nearest neighbor search (ANNS) is a task that finds the approximate nearest neighbors among a high-dimensional dataset for a query via a well-designed index. According to the index adopted, the existing ANNS algorithms can be divided into four major types: hashing-based; tree-based; quantization-based; and graph-based algorithms. Recently, graph-based algorithms have emerged as a highly effective option for ANNS. Thanks to graph-based ANNS algorithms' extraordinary ability to express neighbor relationships, they only need to evaluate fewer points of dataset to receive more accurate results, comparing to other categories.

## Install

This project supports MacOS, Linux, and Windows platforms, requiring [CGraph](https://github.com/ChunelFeng/CGraph). You can download this project by runing the following instructions.

```
git clone --recursive https://github.com/whenever5225/GraphANNS.git
```

If you are a developer using CLion as the IDE, you can open the `CMakeLists.txt` file as a project for compiling. 

## Usage
You need to configure the data file, index file, and parameters in [here](https://github.com/whenever5225/GraphANNS/blob/main/src/elements/nodes/config_nodes/config_alg/) (please refer to [here](http://corpus-texmex.irisa.fr/) for test data download). Suppose you use 'npg' algorithm and '[siftsmall](ftp://ftp.irisa.fr/local/texmex/corpus/siftsmall.tar.gz)' dataset, you can modify the data path to yours in its configure file (`config_npg.h`):

```cpp
class ConfigNPG : public ConfigBasic {
public:
    CStatus init() override {
        CStatus status = CGRAPH_CREATE_GPARAM(ParamNPG, GRAPH_INFO_PARAM_KEY);
        return status;
    }

    CStatus run() override {
        auto *npg_param = CGRAPH_GET_GPARAM(ParamNPG, GRAPH_INFO_PARAM_KEY);
        CGRAPH_ASSERT_NOT_NULL(npg_param);
        npg_param->base_path = "your_base_data_root_path/siftsmall/siftsmall_base.fvecs";	// 'fvecs' format
        npg_param->query_path = "your_query_data_root_path/siftsmall/siftsmall_query.fvecs";	// 'fvecs' format
        npg_param->groundtruth_path = "your_truth_result_root_path/siftsmall/siftsmall_groundtruth.ivecs";	// 'ivecs' format

        npg_param->index_path = "your_index_root_path/index_file_name";	// binary file

        npg_param->L_candidate = 100;
        npg_param->R_neighbor = 100;
        npg_param->C_neighbor = 200;
        npg_param->k_init_graph = 20;
        return CStatus();
    }
};
```

HINT: Please refer [here](http://corpus-texmex.irisa.fr/) for the desciption of `fvecs/ivecs` format. 