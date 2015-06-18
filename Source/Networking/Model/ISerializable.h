/*
	This project is released under the GPL 2.0 license.
	Some parts are based on research by Bas Timmer.
	Please do no evil.
	Initial author: (https://github.com/)Convery
	Started: 2015-03-16
	Notes:
 Interface for formating objects.
 */

#pragma once

namespace Network
{
    class ISerializable
    {
    public:
        virtual void Serialize(ByteBuffer *Buffer);
        virtual void Deserialize(ByteBuffer *Buffer);
    };
    
    inline void ISerializable::Serialize(ByteBuffer *Buffer)
    {
        
    }
    inline void ISerializable::Deserialize(ByteBuffer *Buffer)
    {
        
    }
}