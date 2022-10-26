#!/bin/sh

# possible options: "siftsmall", "SIFT1M", ...
DATASET="siftsmall"

dataset() {
  MODAL1_BASE_PATH="../doc/dataset/${DATASET}/${DATASET}_modal1_base.fvecs"
  MODAL2_BASE_PATH="../doc/dataset/${DATASET}/${DATASET}_modal2_base.ivecs"
  MODAL1_QUERY_PATH="../doc/dataset/${DATASET}/${DATASET}_modal1_query.fvecs"
  MODAL2_QUERY_PATH="../doc/dataset/${DATASET}/${DATASET}_modal2_query.ivecs"
  GROUNDTRUTH_PATH="../doc/dataset/${DATASET}/${DATASET}_gt.ivecs"

}