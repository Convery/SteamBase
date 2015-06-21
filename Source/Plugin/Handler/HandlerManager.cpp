#include "..\..\STDInclude.h"


void HandlerManager::SendEvent(ByteBuffer *inBuffer, void* outBuffer, uint32_t* outLen, int flags)
{
	uint32_t messageType = inBuffer->ReadUInt32();

	switch (messageType){
	
		//createLobby
		case 1:{
			uint64_t sessionId = Nodes::ClientNode::CreateSession(inBuffer, 0);
			ByteBuffer out;
			out.WriteUInt64(sessionId);
			out.Rewind();
			void* readBuffer = out.GetBuffer<void>();
			memcpy(outBuffer, readBuffer, out.GetLength());
			*outLen = out.GetLength();
		}
		case 2:{
			Nodes::ClientNode::UpdateSession(inBuffer, 0);
		}
		case 3:{
			Nodes::ClientNode::FindSessions(inBuffer, 0, outBuffer, outLen);
		}
		case 4:{
			Nodes::ClientNode::DeleteSession(inBuffer, 0);
		}
	}
}