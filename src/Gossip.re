module Node = {
  type t = {identifier: int64};
  let compare = ({identifier: id1}, {identifier: id2}) => Int64.compare(id1, id2);
  module Set =
    Set.Make(
      {
        type nonrec t = t;
        let compare = compare;
      }
    );
};

module GossipOverview = {
  type t = {
    seen: Node.Set.t,
    reachability: bool
  };
};

module VectorClock = {
  module VectorMap = Map.Make(Node);
  type t = VectorMap.t(int);
};

module Gossip = {
  type t = {
    members: Node.Set.t,
    overview: GossipOverview.t,
    version: VectorClock.t
  };
};