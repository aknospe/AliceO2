SET(MODULE_NAME TOFBase)

O2_SETUP(NAME ${MODULE_NAME})

set(SRCS
  src/Geo.cxx
)

set(HEADERS
  include/${MODULE_NAME}/Geo.h
)

SET(LINKDEF src/TOFBaseLinkDef.h)
SET(LIBRARY_NAME ${MODULE_NAME})
SET(BUCKET_NAME emcal_base_bucket)

O2_GENERATE_LIBRARY()

set(TEST_SRCS
  test/testTOFIndex.cxx
)

O2_GENERATE_TESTS(
  MODULE_LIBRARY_NAME ${LIBRARY_NAME}
  BUCKET_NAME ${BUCKET_NAME}
  TEST_SRCS ${TEST_SRCS}
)
