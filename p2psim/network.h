#ifndef __NETWORK_H
#define __NETWORK_H

#include <map>
using namespace std;

#include <lib9.h>
#include <thread.h>

#include "node.h"
#include "packet.h"
#include "topology.h"
#include "threaded.h"

class Network : public Threaded {

public:
  static Network* Instance() { return Instance(0); }
  static Network* Instance(Topology*);
  Channel* pktchan() { return _pktchan; }
  Channel* nodechan() { return _nodechan; }
  Node* getnode(NodeID id) { return _nodes[id]; }
  Topology *gettopology() { return _top; }

private:
  Network(Topology*);
  ~Network();
  virtual void run();

  static Network *_instance;

  map<NodeID, Node*> _nodes;
  Topology *_top;

  Channel *_pktchan;
  Channel *_nodechan;
};

#endif // __NETWORK_H