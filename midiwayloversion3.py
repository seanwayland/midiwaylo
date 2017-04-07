
################################
from pyo import *

# Variables
MAXVOICES = 20
pm_list_devices()
s = Server()
s.setMidiInputDevice(1) # Opens all devices
s.setMidiOutputDevice(8)

s.boot()
# No need to declare variable as global here
waylotrans = 0

# Keep track of played pitches.
playing = {}

def onNoteOn(which):
    global waylotrans
    pit = n["pitch"].get(True)[which]
    
    vel = n["velocity"].get(True)[which]
    vel = int(vel * 127)
    if int(pit) < 60:
        waylotrans = int(pit) - 48
    else:
        pity = int(pit) + waylotrans -12
        # associate the real key (index) to transposed key (value)
        playing[pit] = pity
        s.noteout(pity, vel)

def onNoteOff(which):
    global waylotrans
    pit = n["pitch"].get(True)[which]
    if int(pit) < 60:
         waylotrans = 0
    else:
        # get back the actual transposed key for the noteoff
        pity = playing[pit]
        # delete the entry in the dictionary
        del playing[pit]
        s.noteout(pity, 0)

n = Notein(poly=MAXVOICES, first=10, last=100)

tfon = TrigFunc(n["trigon"], onNoteOn, list(range(MAXVOICES)))
tfoff = TrigFunc(n["trigoff"], onNoteOff, list(range(MAXVOICES)))

s.gui(locals())
#########################
