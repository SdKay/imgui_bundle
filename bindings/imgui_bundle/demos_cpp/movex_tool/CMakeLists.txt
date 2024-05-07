file(GLOB sources *.cpp)

set(MOVEX_ROOT "/home/yanxinxing/Workspace/movex")
set(MOVEX_CACHE_ID "dc06f4b455f9f56ece82f9f75c2e6d72")
set(BAZEL_BIN "${MOVEX_ROOT}/.cache/bazel/${MOVEX_CACHE_ID}/execroot/apollo/bazel-out/k8-fastbuild/bin")
set(BAZEL_EXTERNAL "${MOVEX_ROOT}/.cache/bazel/${MOVEX_CACHE_ID}/external")

include_directories(
  "third"
  "${MOVEX_ROOT}"
  "${BAZEL_BIN}"
  "${MOVEX_ROOT}/third_party/concurrent_queue/"
  "${BAZEL_EXTERNAL}/com_github_google_glog/src"
  "${BAZEL_EXTERNAL}/com_google_protobuf/src"
  "${BAZEL_BIN}/external/com_github_google_glog/src"
)
link_directories(
  "third"
)
# add_demo_cpp(mtool ${sources})
set(args ${ARGN})
list(GET args 0 demo_name)
# imgui_bundle_add_app(mtool ${sources})

hello_imgui_add_app(mtool ${sources})
# target_link_libraries(${app_name} PRIVATE imgui_bundle)
# target_link_libraries(mtool PUBLIC demo_utils safec fastcdr fastrtps scheduler timer_component scheduler_factory node)
target_link_libraries(mtool PUBLIC imgui_bundle demo_utils
  # cyber_core scheduler_factory node binary global_data cyber_conf_proto
  # safec fastcdr libfastrtps.a
  # cyber_core
  # "$<LINK_GROUP:cyber_full,node,binary,file,topology_manager>"
  # cyber_core scheduler_factory
  # node  binary file topology_manager
  # participant transport_conf_proto global_data node_manager
  # topology_change_proto manager pin_thread
  # choreography_context classic_conf_proto cyber_conf_proto
  # choreography_conf_proto role_attributes_proto underlay_message
  # clock duration rate time participant_listener underlay_message_type
  # channel_manager graph multi_value_warehouse role service_manager
  # single_value_warehouse topology_manager
  # qos_profile_proto scheduler_conf_proto
  
  # scheduler scheduler_factory scheduler_classic scheduler_choreography scheduler_conf_proto
  # scheduler_full
  # glog gflags protobuf protobuf_lite
  # safec fastcdr libfastrtps.a
  # tinyxml2
)

