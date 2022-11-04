#!/bin/sh

source dataset.sh

dataset

# possible options: "MultimodalSimilarityAggregationGraph"("MSAG"), "MultimodalSimilarityAggregationBruteforce"("MSAB"),
# "MultichannelAggregationByGraph"("MABG"), "MultichannelAggregationByBruteforce"("MABB")
STRATEGY="MABB"
INDEX_PREFIX_PATH=../doc/index/${DATASET}
INDEX_PATH=${INDEX_PREFIX_PATH}/${DATASET}_${STRATEGY}.index
IS_NORM_MODAL1=1 # 0 for siftsmall; 1 for celeba
IS_NORM_MODAL2=0 # 0 for siftsmall, celeba,
IS_SKIP_NUM=1 # 1 for celeba, 0 for siftsmall
SKIP_NUM=0 # 0 for celeba
IS_MULTI_RESULT_EQUAL=1  # 1 for celeba, 0 for siftsmall
BUILD_THREAD_NUM=8
SEARCH_THREAD_NUM=1
TOPK=10
GTK=10

param_siftsmall_MSAG() {
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
  IS_NORM_MODAL1=0
  IS_NORM_MODAL2=0
  IS_SKIP_NUM=0
  IS_MULTI_RESULT_EQUAL=0
  IS_DELETE_ID=0

  L_search=200
}

param_celeba_MSAG() {
  W1=-0.2
  W2=-0.3
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
  IS_NORM_MODAL1=1
  IS_NORM_MODAL2=0
  IS_SKIP_NUM=1
  IS_MULTI_RESULT_EQUAL=1
  IS_DELETE_ID=1

  TOPK=1
  GTK=1
  L_search=200
}

param_siftsmall_MSAB() {
  SEARCH_THREAD_NUM=8
  W1=-0.5
  W2=-0.5
  IS_SKIP_NUM=0
  SKIP_NUM=0
  IS_MULTI_RESULT_EQUAL=0
  IS_DELETE_ID=0
  TOPK=10
  GTK=10
}

param_celeba_MSAB() {
  SEARCH_THREAD_NUM=32
  W1=-0.2
  W2=0
  IS_SKIP_NUM=1
  SKIP_NUM=0
  IS_MULTI_RESULT_EQUAL=1
  IS_DELETE_ID=1
  TOPK=1
  GTK=1
}

param_siftsmall_MABG() {
  IS_NORM_MODAL1=0
  IS_NORM_MODAL2=0
  IS_SKIP_NUM=0
  IS_MULTI_RESULT_EQUAL=0
  IS_DELETE_ID=0
  W1=-1
  W2=-1
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
  INDEX_PATH_MODAL1=${INDEX_PREFIX_PATH}/${DATASET}_${STRATEGY}_modal1.index
  INDEX_PATH_MODAL2=${INDEX_PREFIX_PATH}/${DATASET}_${STRATEGY}_modal2.index

  TOPK=100
  GTK=10
  L_search=200
}

param_celeba_MABG() {
  IS_NORM_MODAL1=1
  IS_NORM_MODAL2=0
  IS_SKIP_NUM=1
  IS_MULTI_RESULT_EQUAL=1
  IS_DELETE_ID=1
  W1=-1
  W2=-1
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
  INDEX_PATH_MODAL1=${INDEX_PREFIX_PATH}/${DATASET}_${STRATEGY}_modal1.index
  INDEX_PATH_MODAL2=${INDEX_PREFIX_PATH}/${DATASET}_${STRATEGY}_modal2.index

  CANDIDATE_TOPK=5
  TOPK=1
  GTK=1
  L_search=20
}

param_siftsmall_MABB() {
  SEARCH_THREAD_NUM=8
  W1=-0.5
  W2=-0.5
  IS_SKIP_NUM=0
  SKIP_NUM=0
  IS_MULTI_RESULT_EQUAL=0
  IS_DELETE_ID=0
  CANDIDATE_TOPK=50
  TOPK=10
  GTK=10
}

param_celeba_MABB() {
  SEARCH_THREAD_NUM=32
  W1=-1
  W2=-1
  IS_SKIP_NUM=1
  SKIP_NUM=0
  IS_MULTI_RESULT_EQUAL=1
  IS_DELETE_ID=1
  CANDIDATE_TOPK=5
  TOPK=1
  GTK=1
}