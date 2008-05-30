/***************************************************************************
 *   Copyright (C) 2005-08 by the Quassel Project                          *
 *   devel@quassel-irc.org                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) version 3.                                           *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef BUFFERVIEWCONFIG_H
#define BUFFERVIEWCONFIG_H

#include "syncableobject.h"

#include "types.h"

class BufferViewConfig : public SyncableObject {
  Q_OBJECT
  Q_PROPERTY(QString bufferViewName READ bufferViewName WRITE setBufferViewName)
  Q_PROPERTY(NetworkId networkId READ networkId WRITE setNetworkId)
  Q_PROPERTY(bool addNewBuffersAutomatically READ addNewBuffersAutomatically WRITE setAddNewBuffersAutomatically)
  Q_PROPERTY(bool sortAlphabetically READ sortAlphabetically WRITE setSortAlphabetically)
  Q_PROPERTY(bool hideInactiveBuffers READ hideInactiveBuffers WRITE setHideInactiveBuffers)
  Q_PROPERTY(int allowedBufferTypes READ allowedBufferTypes WRITE setAllowedBufferTypes)
  Q_PROPERTY(int minimumActivity READ minimumActivity WRITE setMinimumActivity)

public:
  BufferViewConfig(int bufferViewId, QObject *parent = 0);
  BufferViewConfig(int bufferViewId, const QVariantMap &properties, QObject *parent = 0);


public slots:
  inline int bufferViewId() const { return _bufferViewId; }

  inline const QString &bufferViewName() const { return _bufferViewName; }
  void setBufferViewName(const QString &bufferViewName);

  inline const NetworkId &networkId() const { return _networkId; }
  void setNetworkId(const NetworkId &networkId);

  inline bool addNewBuffersAutomatically() const { return _addNewBuffersAutomatically; }
  void setAddNewBuffersAutomatically(bool addNewBuffersAutomatically);

  inline bool sortAlphabetically() const { return _sortAlphabetically; }
  void setSortAlphabetically(bool sortAlphabetically);

  inline int allowedBufferTypes() const { return _allowedBufferTypes; }
  void setAllowedBufferTypes(int bufferTypes);

  inline int minimumActivity() const { return _minimumActivity; }
  void setMinimumActivity(int activity);

  inline bool hideInactiveBuffers() const { return _hideInactiveBuffers; }
  void setHideInactiveBuffers(bool hideInactiveBuffers);
  
  virtual inline void requestSetBufferViewName(const QString &bufferViewName) { emit setBufferViewNameRequested(bufferViewName); }

  const QList<BufferId> &bufferList() const { return _buffers; }
  const QSet<BufferId> &removedBuffers() const { return _removedBuffers; }
  const QSet<BufferId> &temporarilyRemovedBuffers() const { return _temporarilyRemovedBuffers; }

  QVariantList initBufferList() const;
  void initSetBufferList(const QVariantList &buffers);
  void initSetBufferList(const QList<BufferId> &buffers);

  QVariantList initRemovedBuffers() const;
  void initSetRemovedBuffers(const QVariantList &buffers);

  QVariantList initTemporarilyRemovedBuffers() const;
  void initSetTemporarilyRemovedBuffers(const QVariantList &buffers);

  void addBuffer(const BufferId &bufferId, int pos);
  virtual inline void requestAddBuffer(const BufferId &bufferId, int pos) { emit addBufferRequested(bufferId, pos); }
  void moveBuffer(const BufferId &bufferId, int pos);
  virtual inline void requestMoveBuffer(const BufferId &bufferId, int pos) { emit moveBufferRequested(bufferId, pos); }
  void removeBuffer(const BufferId &bufferId);
  virtual inline void requestRemoveBuffer(const BufferId &bufferId) { emit removeBufferRequested(bufferId); }
  void removeBufferPermanently(const BufferId &bufferId);
  virtual inline void requestRemoveBufferPermanently(const BufferId &bufferId) { emit removeBufferPermanentlyRequested(bufferId); }
  
  
signals:
  void bufferViewNameSet(const QString &bufferViewName);
  void networkIdSet(const NetworkId &networkId);
  void addNewBuffersAutomaticallySet(bool addNewBuffersAutomatically);
  void sortAlphabeticallySet(bool sortAlphabetically);  
  void allowedBufferTypesSet(int allowedBufferTypes);
  void minimumActivitySet(int activity);
  void hideInactiveBuffersSet(bool hideInactiveBuffers);
  void bufferListSet();

  void bufferAdded(const BufferId &bufferId, int pos);
  void addBufferRequested(const BufferId &bufferId, int pos);
  void bufferMoved(const BufferId &bufferId, int pos);
  void moveBufferRequested(const BufferId &bufferId, int pos);
  void bufferRemoved(const BufferId &bufferId);
  void bufferPermanentlyRemoved(const BufferId &bufferId);
  void removeBufferRequested(const BufferId &bufferId);
  void removeBufferPermanentlyRequested(const BufferId &bufferId);
  
  void setBufferViewNameRequested(const QString &bufferViewName);

private:
  int _bufferViewId;
  QString _bufferViewName;
  NetworkId _networkId;
  bool _addNewBuffersAutomatically;
  bool _sortAlphabetically;
  bool _hideInactiveBuffers;
  int _allowedBufferTypes;
  int _minimumActivity;
  QList<BufferId> _buffers;
  QSet<BufferId> _removedBuffers;
  QSet<BufferId> _temporarilyRemovedBuffers;
};

#endif // BUFFERVIEWCONFIG_H
