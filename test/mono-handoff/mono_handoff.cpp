#include <catch.hpp>

#include "opnmidi.h"

namespace
{
class Player
{
public:
    Player()
        : device(opn2_init(49716))
    {}

    ~Player()
    {
        if(device)
            opn2_close(device);
    }

    OPN2_MIDIPlayer *get() const
    {
        return device;
    }

private:
    OPN2_MIDIPlayer *device;
};
}

TEST_CASE("[OPNMIDI realtime mono] handoff replaces the old note immediately")
{
    Player player;
    REQUIRE(player.get() != 0);

    const OPN2_UInt8 channel = 0;
    const OPN2_UInt8 oldNote = 60;
    const OPN2_UInt8 newNote = 64;

    REQUIRE(opn2_rt_noteOn(player.get(), channel, oldNote, 100) == 1);

    /*
     * Intended future API:
     *   opn2_rt_monoHandoff(device, channel, oldNote, newNote, velocity)
     *
     * It should atomically replace oldNote with newNote on the same MIDI
     * channel for true mono realtime playback. The old note must be muted or
     * detached immediately instead of being allowed to continue as a release
     * tail that overlaps the new note.
     *
     * After implementation exposes either active-note inspection or a stable
     * render fixture, add an audio assertion here: render a short block before
     * and after handoff and verify the transition does not contain a measurable
     * old-note release tail or a large discontinuity spike.
     */
    REQUIRE(opn2_rt_monoHandoff(player.get(), channel, oldNote, newNote, 100) == 1);

    opn2_rt_noteOff(player.get(), channel, newNote);
}
