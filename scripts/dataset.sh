#!/bin/sh

# possible options: "siftsmall", "SIFT1M", "celeba", ...
DATASET="celeba"

dataset() {
  case $DATASET in
    siftsmall)
      MODAL1_BASE_PATH="../doc/dataset/${DATASET}/${DATASET}_modal1_base.fvecs"
      MODAL2_BASE_PATH="../doc/dataset/${DATASET}/${DATASET}_modal2_base.ivecs"
      MODAL1_QUERY_PATH="../doc/dataset/${DATASET}/${DATASET}_modal1_query.fvecs"
      MODAL2_QUERY_PATH="../doc/dataset/${DATASET}/${DATASET}_modal2_query.ivecs"
      GROUNDTRUTH_PATH="../doc/dataset/${DATASET}/${DATASET}_gt.ivecs"
    ;;
    celeba)
      MODAL1_BASE_PATH="../doc/dataset/${DATASET}/test/${DATASET}_modal1_base.fvecs"
      MODAL2_BASE_PATH="../doc/dataset/${DATASET}/test/${DATASET}_modal2_base.ivecs"
      MODAL1_QUERY_PATH="../doc/dataset/${DATASET}/test/${DATASET}_modal1_2_query.fvecs"
      MODAL2_QUERY_PATH="../doc/dataset/${DATASET}/test/${DATASET}_modal2_query.ivecs"
      GROUNDTRUTH_PATH="../doc/dataset/${DATASET}/test/${DATASET}_gt.ivecs"
    ;;
    ImageText1M|AudioText1M|VideoText1M)
      MODAL1_BASE_PATH="/home/zjlab/ANNS/dataset/siftsmall/siftsmall_base.fvecs"
      MODAL2_BASE_PATH="../doc/dataset/${DATASET}/${DATASET}_modal2_base.ivecs"
      MODAL1_QUERY_PATH="/home/zjlab/ANNS/dataset/siftsmall/siftsmall_query.fvecs"
      MODAL2_QUERY_PATH="../doc/dataset/${DATASET}/${DATASET}_modal2_query.ivecs"
      GROUNDTRUTH_PATH="../doc/dataset/${DATASET}/${DATASET}_gt.ivecs"
  esac
}