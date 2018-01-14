type failureDetectionProtocol =
  | Ping
  | PingRequest
  | Ack;

type disseminationProtocol =
  | Alive
  | Suspect
  | ConfirmFault;

type msg =
  | Join
  | Leave;