#!/bin/sh

source dataset.sh

dataset

# possible options: "MultimodalGraph"("MG"), "MultimodalBruteforce"("MB")
STRATEGY="MB"
INDEX_PREFIX_PATH=../doc/index/${DATASET}
INDEX_PATH=${INDEX_PREFIX_PATH}/${DATASET}_${STRATEGY}.index
IS_NORM_MODAL1=1
IS_NORM_MODAL2=0
IS_SKIP_NUM=1
SKIP_NUM=0
IS_MULTI_RESULT_EQUAL=1  #Hightlight
BUILD_THREAD_NUM=8
SEARCH_THREAD_NUM=1
TOPK=10
GTK=1

param_siftsmall_MG() {
  W1=-0.5
  W2=-0.5
  L_candidate=100
  R_neighbor=30
  C_neighbor=200
  k_init_graph=100
  nn_size=50
  rnn_size=25
  pool_size=200
  iter=8
  sample_num=100
  graph_quality_threshold=0.8

  L_search=30
}

param_celeba_MB() {
  SEARCH_THREAD_NUM=32
  W1=-0.2
  W2=-0.3
  IS_SKIP_NUM=1
  SKIP_NUM=0
  IS_MULTI_RESULT_EQUAL=1
  TOPK=10
  GTK=1
}

param_siftsmall_MB() {
  SEARCH_THREAD_NUM=8
  W1=-0.5
  W2=-0.5
  IS_SKIP_NUM=0
  SKIP_NUM=0
  IS_MULTI_RESULT_EQUAL=0
  TOPK=10
  GTK=10
}
