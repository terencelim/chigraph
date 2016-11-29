#include "NodeState.hpp"

#include "NodeDataModel.hpp"

#include "Connection.hpp"

NodeState::
NodeState(std::unique_ptr<NodeDataModel> const &model)
  : _outConnections(model->nPorts(PortType::Out))
  , _inConnections(model->nPorts(PortType::In))
  , _reaction(NOT_REACTING)
  , _reactingPortType(PortType::None)
  , _resizing(false)
{
}


std::vector<NodeState::ConnectionPtrSet> const &
NodeState::
getEntries(PortType portType) const
{
  if (portType == PortType::In)
    return _inConnections;
  else
    return _outConnections;
}


std::vector<NodeState::ConnectionPtrSet> &
NodeState::
getEntries(PortType portType)
{
  if (portType == PortType::In)
    return _inConnections;
  else
    return _outConnections;
}


NodeState::ConnectionPtrSet
NodeState::
connections(PortType portType, PortIndex portIndex) const
{
  auto const &connections = getEntries(portType);

  return connections[portIndex];
}


void
NodeState::
setConnection(PortType portType,
              PortIndex portIndex,
              std::shared_ptr<Connection> connection)
{
  auto &connections = getEntries(portType);

  connections[portIndex].emplace(connection->id(),
                                 connection);
}


void
NodeState::
eraseConnection(PortType portType,
                PortIndex portIndex,
                QUuid id)
{
  getEntries(portType)[portIndex].erase(id);
}


NodeState::ReactToConnectionState
NodeState::
reaction() const
{
  return _reaction;
}


PortType
NodeState::
reactingPortType() const
{
  return _reactingPortType;
}


NodeDataType
NodeState::
reactingDataType() const
{
  return _reactingDataType;
}


void
NodeState::
setReaction(ReactToConnectionState reaction,
            PortType reactingPortType,
            NodeDataType reactingDataType)
{
  _reaction = reaction;

  _reactingPortType = reactingPortType;

  _reactingDataType = reactingDataType;
}


bool
NodeState::
isReacting() const
{
  return _reaction == REACTING;
}


void
NodeState::
setResizing(bool resizing)
{
  _resizing = resizing;
}


bool
NodeState::
resizing() const
{
  return _resizing;
}