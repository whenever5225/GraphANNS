#!/bin/bash

set -e
source param.sh

param_${DATASET}_${STRATEGY}

TIME=(`date +%Y_%m_%d`)
RESULT_PREFIX_PATH="../doc/result/${TIME}"
SEARCH_RESULT_PATH=${RESULT_PREFIX_PATH}/${DATASET}_${STRATEGY}_res.txt
#SEARCH_RESULT_PATH=" "

if [ ! -e ${RESULT_PREFIX_PATH} ]
then
mkdir -p ${RESULT_PREFIX_PATH}
echo "${RESULT_PREFIX_PATH} is set."
fi

if [ ! -e ${INDEX_PREFIX_PATH} ]
then
mkdir -p ${INDEX_PREFIX_PATH}
echo "${INDEX_PREFIX_PATH} is set."
fi

print_usage_and_exit() {
  echo "[SCRIPT] Usage: ./run.sh [debug/release] [build_${STRATEGY}/search_$STRATEGY}]"
  exit 1
}

check_dir_and_make_if_absent() {
  local dir=$1
  if [ -d $dir ]; then
    echo "[SCRIPT] Directory $dir is already exit. Remove or rename it and then re-run."
    exit 1
  else
    mkdir -p ${dir}
  fi
}

# compiling
case $1 in
  debug)
    cmake -DCMAKE_BUILD_TYPE=Debug .. -B ../debug
    EXE_PATH=../debug
  ;;
  release)
    cmake -DCMAKE_BUILD_TYPE=Release .. -B ../release
    EXE_PATH=../release
  ;;
  *)
    print_usage_and_exit
  ;;
esac
pushd $EXE_PATH
make -j
popd

case $2 in
  build_MSAG)
    echo "[SCRIPT] Building MultimodalSimilarityAggregationGraph index on ${DATASET} ..."
    time $EXE_PATH/T-MSAG \
      ${MODAL1_BASE_PATH} \
      ${MODAL2_BASE_PATH} \
      ${INDEX_PATH} \
      ${BUILD_THREAD_NUM} \
      ${W1} \
      ${W2} \
      ${L_candidate} \
      ${R_neighbor} \
      ${C_neighbor} \
      ${k_init_graph} \
      ${nn_size} \
      ${rnn_size} \
      ${pool_size} \
      ${iter} \
      ${sample_num} \
      ${graph_quality_threshold} \
      ${IS_NORM_MODAL1} \
      ${IS_NORM_MODAL2} \
      ${IS_SKIP_NUM} \
      ${SKIP_NUM} >> ${RESULT_PREFIX_PATH}/build_${STRATEGY}.log
  ;;
  build_MABG)
    echo "[SCRIPT] Modal1: Building MultichannelAggregationByGraph index on ${DATASET} ..."
    time $EXE_PATH/T-MSAG \
      ${MODAL1_BASE_PATH} \
      ${MODAL2_BASE_PATH} \
      ${INDEX_PATH_MODAL1} \
      ${BUILD_THREAD_NUM} \
      ${W1} \
      0 \
      ${L_candidate} \
      ${R_neighbor} \
      ${C_neighbor} \
      ${k_init_graph} \
      ${nn_size} \
      ${rnn_size} \
      ${pool_size} \
      ${iter} \
      ${sample_num} \
      ${graph_quality_threshold} \
      ${IS_NORM_MODAL1} \
      ${IS_NORM_MODAL2} \
      ${IS_SKIP_NUM} \
      ${SKIP_NUM} >> ${RESULT_PREFIX_PATH}/build_${STRATEGY}.log
    echo "[SCRIPT] Modal2: Building MultichannelAggregationByGraph index on ${DATASET} ..."
    time $EXE_PATH/T-MSAG \
      ${MODAL1_BASE_PATH} \
      ${MODAL2_BASE_PATH} \
      ${INDEX_PATH_MODAL2} \
      ${BUILD_THREAD_NUM} \
      0 \
      ${W2} \
      ${L_candidate} \
      ${R_neighbor} \
      ${C_neighbor} \
      ${k_init_graph} \
      ${nn_size} \
      ${rnn_size} \
      ${pool_size} \
      ${iter} \
      ${sample_num} \
      ${graph_quality_threshold} \
      ${IS_NORM_MODAL1} \
      ${IS_NORM_MODAL2} \
      ${IS_SKIP_NUM} \
      ${SKIP_NUM} >> ${RESULT_PREFIX_PATH}/build_${STRATEGY}.log
  ;;
  search_MABG)
    echo "[SCRIPT] Searching by MultichannelAggregationByGraph on ${DATASET} ..."
    time $EXE_PATH/S-MABG \
      ${MODAL1_BASE_PATH} \
      ${MODAL2_BASE_PATH} \
      ${MODAL1_QUERY_PATH} \
      ${MODAL2_QUERY_PATH} \
      ${GROUNDTRUTH_PATH} \
      ${INDEX_PATH_MODAL1} \
      ${INDEX_PATH_MODAL2} \
      ${SEARCH_RESULT_PATH} \
      ${SEARCH_THREAD_NUM} \
      ${W1} \
      ${W2} \
      ${TOPK} \
      ${GTK} \
      ${L_search} \
      ${IS_NORM_MODAL1} \
      ${IS_NORM_MODAL2} \
      ${IS_SKIP_NUM} \
      ${SKIP_NUM} \
      ${IS_MULTI_RESULT_EQUAL} \
      ${IS_DELETE_ID} \
      ${DELETE_ID_PATH} \
      ${CANDIDATE_TOPK} >> ${RESULT_PREFIX_PATH}/search_${STRATEGY}.log
  ;;
  search_MSAG)
    echo "[SCRIPT] Searching by MultimodalSimilarityAggregationGraph on ${DATASET} ..."
    time $EXE_PATH/S-MSAG \
      ${MODAL1_BASE_PATH} \
      ${MODAL2_BASE_PATH} \
      ${MODAL1_QUERY_PATH} \
      ${MODAL2_QUERY_PATH} \
      ${GROUNDTRUTH_PATH} \
      ${INDEX_PATH} \
      ${SEARCH_RESULT_PATH} \
      ${SEARCH_THREAD_NUM} \
      ${W1} \
      ${W2} \
      ${TOPK} \
      ${GTK} \
      ${L_search} \
      ${IS_NORM_MODAL1} \
      ${IS_NORM_MODAL2} \
      ${IS_SKIP_NUM} \
      ${SKIP_NUM} \
      ${IS_MULTI_RESULT_EQUAL} \
      ${IS_DELETE_ID} \
      ${DELETE_ID_PATH} >> ${RESULT_PREFIX_PATH}/search_${STRATEGY}.log
  ;;
  search_MSAB)
    echo "[SCRIPT] Searching by MultimodalSimilarityAggregationBruteforce on ${DATASET} ..."
    time $EXE_PATH/S-MSAB \
      ${MODAL1_BASE_PATH} \
      ${MODAL2_BASE_PATH} \
      ${MODAL1_QUERY_PATH} \
      ${MODAL2_QUERY_PATH} \
      ${GROUNDTRUTH_PATH} \
      ${SEARCH_RESULT_PATH} \
      ${SEARCH_THREAD_NUM} \
      ${W1} \
      ${W2} \
      ${TOPK} \
      ${GTK} \
      ${IS_NORM_MODAL1} \
      ${IS_NORM_MODAL2} \
      ${IS_SKIP_NUM} \
      ${SKIP_NUM} \
      ${IS_MULTI_RESULT_EQUAL} \
      ${IS_DELETE_ID} \
      ${DELETE_ID_PATH} >> ${RESULT_PREFIX_PATH}/search_${STRATEGY}.log
  ;;
  search_MABB)
    echo "[SCRIPT] Searching by MultichannelAggregationByBruteforce on ${DATASET} ..."
    time $EXE_PATH/S-MABB \
      ${MODAL1_BASE_PATH} \
      ${MODAL2_BASE_PATH} \
      ${MODAL1_QUERY_PATH} \
      ${MODAL2_QUERY_PATH} \
      ${GROUNDTRUTH_PATH} \
      ${SEARCH_RESULT_PATH} \
      ${SEARCH_THREAD_NUM} \
      ${W1} \
      ${W2} \
      ${TOPK} \
      ${GTK} \
      ${IS_NORM_MODAL1} \
      ${IS_NORM_MODAL2} \
      ${IS_SKIP_NUM} \
      ${SKIP_NUM} \
      ${IS_MULTI_RESULT_EQUAL} \
      ${IS_DELETE_ID} \
      ${DELETE_ID_PATH} \
      ${CANDIDATE_TOPK} >> ${RESULT_PREFIX_PATH}/search_${STRATEGY}.log
  ;;
esac