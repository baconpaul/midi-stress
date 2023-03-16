#include <iostream>

#include "RtMidi.h"

int main(int, char **)
{
  std::cout << "Hello World" <<std::endl;

  auto midiin = std::make_unique<RtMidiIn>();
unsigned int nPorts = midiin->getPortCount();
      std::cout << "\nThere are " << nPorts << " MIDI input sources available.\n";

      for ( unsigned i=0; i<nPorts; i++ ) {
        std::string portName = midiin->getPortName(i);
        std::cout << "  Input Port #" << i << ": " << portName << '\n';
      }

  return 0;
}
