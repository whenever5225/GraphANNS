#!/bin/sh

# 'DATASET' possible options: "siftsmall", "SIFT1M", "celeba_tirg", ...
# 'DATASET_SUFFIX' possible options: "tirg_encode", "resnet_encode"
DATASET="celeba"
DATASET_SUFFIX="tirg_encode"

dataset() {
  case $DATASET in
    siftsmall)
      MODAL1_BASE_PATH="../doc/dataset/${DATASET}/${DATASET}_modal1_base.fvecs"
      MODAL2_BASE_PATH="../doc/dataset/${DATASET}/${DATASET}_modal2_base.ivecs"
      MODAL1_QUERY_PATH="../doc/dataset/${DATASET}/${DATASET}_modal1_query.fvecs"
      MODAL2_QUERY_PATH="../doc/dataset/${DATASET}/${DATASET}_modal2_query.ivecs"
      GROUNDTRUTH_PATH="../doc/dataset/${DATASET}/${DATASET}_gt.ivecs"
      DELETE_ID_PATH="NULL"
    ;;
    celeba)
      MODAL2_BASE_PATH="../doc/dataset/${DATASET}/test/${DATASET}_modal2_base.ivecs"
      MODAL2_QUERY_PATH="../doc/dataset/${DATASET}/test/${DATASET}_modal2_query.ivecs"
      GROUNDTRUTH_PATH="../doc/dataset/${DATASET}/test/${DATASET}_gt.ivecs"
      DELETE_ID_PATH="../doc/dataset/${DATASET}/test/${DATASET}_delete_id.ivecs"
      case $DATASET_SUFFIX in
        tirg_encode)
          MODAL1_BASE_PATH="../doc/dataset/${DATASET}/test/${DATASET_SUFFIX}/${DATASET}_modal1_base.fvecs"
          MODAL1_QUERY_PATH="../doc/dataset/${DATASET}/test/${DATASET_SUFFIX}/${DATASET}_modal1_2_query.fvecs"
        ;;
        resnet_encode)
          MODAL1_BASE_PATH="../doc/dataset/${DATASET}/test/${DATASET_SUFFIX}/${DATASET}_modal1_base.fvecs"
          MODAL1_QUERY_PATH="../doc/dataset/${DATASET}/test/${DATASET_SUFFIX}/${DATASET}_modal1_query.fvecs"
      esac
    ;;
    ImageText1M|AudioText1M|VideoText1M)
      MODAL1_BASE_PATH="/home/zjlab/ANNS/dataset/siftsmall/siftsmall_base.fvecs"
      MODAL2_BASE_PATH="../doc/dataset/${DATASET}/${DATASET}_modal2_base.ivecs"
      MODAL1_QUERY_PATH="/home/zjlab/ANNS/dataset/siftsmall/siftsmall_query.fvecs"
      MODAL2_QUERY_PATH="../doc/dataset/${DATASET}/${DATASET}_modal2_query.ivecs"
      GROUNDTRUTH_PATH="../doc/dataset/${DATASET}/${DATASET}_gt.ivecs"
      DELETE_ID_PATH="NULL"
  esac
}