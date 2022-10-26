#!/bin/bash

set -e
source param.sh

param_${DATASET}_${STRATEGY}

TIME=(`date +%Y_%m_%d`)
RESULT_PREFIX_PATH="../doc/result/${TIME}"

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
  build_MG)
    echo "[SCRIPT] Building MultimodalGraph index on ${DATASET} ..."
    time $EXE_PATH/T-MG \
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
      ${graph_quality_threshold} >> ${RESULT_PREFIX_PATH}/build_${STRATEGY}.log
  ;;
  search_MG)
    echo "[SCRIPT] Searching by MultimodalGraph on ${DATASET} ..."
    time $EXE_PATH/S-MG \
      ${MODAL1_BASE_PATH} \
      ${MODAL2_BASE_PATH} \
      ${MODAL1_QUERY_PATH} \
      ${MODAL2_QUERY_PATH} \
      ${GROUNDTRUTH_PATH} \
      ${INDEX_PATH} \
      ${SEARCH_THREAD_NUM} \
      ${W1} \
      ${W2} \
      ${TOPK} \
      ${L_search} >> ${RESULT_PREFIX_PATH}/search_${STRATEGY}.log
  ;;
  search_MB)
    echo "[SCRIPT] Searching by MultimodalBruteforce on ${DATASET} ..."
    time $EXE_PATH/S-MB \
      ${MODAL1_BASE_PATH} \
      ${MODAL2_BASE_PATH} \
      ${MODAL1_QUERY_PATH} \
      ${MODAL2_QUERY_PATH} \
      ${GROUNDTRUTH_PATH} \
      ${SEARCH_THREAD_NUM} \
      ${W1} \
      ${W2} \
      ${TOPK} >> ${RESULT_PREFIX_PATH}/search_${STRATEGY}.log
  ;;
esac