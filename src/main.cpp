#include <iostream>

#include "RtMidi.h"
#include <isocline.h>

int main(int, char **)
{
  std::cout << "Hello World" <<std::endl;

  auto midiout = std::make_unique<RtMidiOut>();
unsigned int nPorts = midiout->getPortCount();
      std::cout << "\nThere are " << nPorts << " MIDI output ports available.\n";

      for ( unsigned i=0; i<nPorts; i++ ) {
        std::string portName = midiout->getPortName(i);
        std::cout << "  Input Port #" << i << ": " << portName << '\n';
      }
ic_set_history(nullptr, -1 /* default entries (= 200) */);
char* input;
while( (input = ic_readline("prompt")) != NULL ) { // ctrl+d/c or errors return NULL
  printf("you typed:\n%s\n", input); // use the input
  free(input);  
}

  return 0;
}
