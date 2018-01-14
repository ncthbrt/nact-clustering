Design

SWIM for failure detection overlaid with a (vector clock/interval clock) based gossip protocol (w/ interval trees/consistent hash-rings, not sure yet)

Then there are two consistency modes Strong/Best Effort/Weak.

In Weak mode the messages routed to node accepts messages regardless of whether the whole cluster is aware of the configuration change.
SWIM is eventually convergent.

In STRONG mode there are two kinds of configuration changes:

1. Forced 
2. Cooperative

These two modes behave symmetrically. 

In forced mode, a result of a node in the cluster behaving badly (i.e. not responding to messages), there is no guarantee that 
the faulted node is not committing writes to an entity in its key space. Thus the nodes who have been assigned responsibility for the faulted node's key space are required to forward messages in the faulted node's key space to the faulted node until there is proof that all other non-faulted nodes in the same cluster have learnt of the fault. This of course will likely result in a partial loss of availability for the nodes in the faulted key-space; however this tradeoff ensures that consistency is maintained (unless the "faulted"/"partitioned" node continues writing based on internal state, however timeouts should mitigate this). Forced mode is a part of the strong consistency model. 

In Cooperative mode, if node has decided it is leaving or shutting down, it gossips the leaving message to other nodes in cluster and immediately stops processing messages. The nodes responsible for the leaving node's key space can start processing messages delivered to it immediately. The node leaving forwards the messages on. Adding a node is just an extension of this behavior: The new node subsumes a portion of another node's key interval. The subsumed node cooperates with the previous node by forwarding its traffic until convergence. The new node only starts processing messages once a cooperation pact has been reached. 