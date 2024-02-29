add_library(cppjieba INTERFACE)
add_library(cppjieba::cppjieba ALIAS cppjieba)
target_sources(cppjieba
    PRIVATE
        include/cppjieba/DictTrie.hpp
        include/cppjieba/FullSegment.hpp
        include/cppjieba/HMMModel.hpp
        include/cppjieba/HMMSegment.hpp
        include/cppjieba/Jieba.hpp
        include/cppjieba/KeywordExtractor.hpp
        include/cppjieba/MPSegment.hpp
        include/cppjieba/MixSegment.hpp
        include/cppjieba/PosTagger.hpp
        include/cppjieba/PreFilter.hpp
        include/cppjieba/QuerySegment.hpp
        include/cppjieba/SegmentBase.hpp
        include/cppjieba/SegmentTagged.hpp
        include/cppjieba/TextRankExtractor.hpp
        include/cppjieba/Trie.hpp
        include/cppjieba/Unicode.hpp
)

target_link_libraries(cppjieba
    INTERFACE
        limonp::limonp
)

ADD_SUBDIRECTORY(deps/limonp)
