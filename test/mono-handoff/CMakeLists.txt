
set(CMAKE_CXX_STANDARD 11)

include_directories (${CMAKE_CURRENT_SOURCE_DIR}/../common
                     ${CMAKE_SOURCE_DIR}/include
                     ${CMAKE_SOURCE_DIR}/src)

add_executable(MonoHandoffTest
               mono_handoff.cpp
               ${libOPNMIDI_SOURCE_DIR}/src/opnmidi.cpp
               ${libOPNMIDI_SOURCE_DIR}/src/opnmidi_load.cpp
               ${libOPNMIDI_SOURCE_DIR}/src/opnmidi_private.cpp
               ${libOPNMIDI_SOURCE_DIR}/src/opnmidi_midiplay.cpp
               ${libOPNMIDI_SOURCE_DIR}/src/opnmidi_opn2.cpp
               ${libOPNMIDI_SOURCE_DIR}/src/wopn/wopn_file.c
               ${libOPNMIDI_SOURCE_DIR}/src/chips/nuked_opn2.cpp
               ${libOPNMIDI_SOURCE_DIR}/src/chips/nuked/ym3438.c
               $<TARGET_OBJECTS:Catch-objects>)

set_target_properties(MonoHandoffTest PROPERTIES COMPILE_DEFINITIONS "GSL_THROW_ON_CONTRACT_VIOLATION")
target_compile_definitions(MonoHandoffTest PRIVATE
  OPNMIDI_DISABLE_MIDI_SEQUENCER
  OPNMIDI_DISABLE_GENS_EMULATOR
  OPNMIDI_DISABLE_MAME_EMULATOR
  OPNMIDI_DISABLE_GX_EMULATOR
  OPNMIDI_DISABLE_NP2_EMULATOR
  OPNMIDI_DISABLE_MAME_2608_EMULATOR)
add_test(NAME MonoHandoffTest COMMAND MonoHandoffTest)
