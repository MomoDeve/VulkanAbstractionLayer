// Copyright(c) 2021, #Momo
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met :
// 
// 1. Redistributions of source code must retain the above copyright notice, this
// list of conditions and the following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and /or other materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#pragma once

#include "Buffer.h"
#include "ArrayUtils.h"

namespace VulkanAbstractionLayer
{
	class StageBuffer
	{
		Buffer buffer;
		uint32_t currentOffset;

	public:
		struct Allocation
		{
			uint32_t Size;
			uint32_t Offset;
		};

		StageBuffer(size_t byteSize);

		Allocation Submit(const uint8_t* data, uint32_t byteSize);
		void Flush();
		void Reset();
		Buffer& GetBuffer() { return this->buffer; }
		const Buffer& GetBuffer() const { return this->buffer; }

		template<typename T>
		Allocation Submit(ArrayView<const T> view)
		{
			return this->Submit((uint8_t*)view.data(), uint32_t(view.size() * sizeof(T)));
		}

		template<typename T>
		Allocation Submit(const T* value)
		{
			return this->Submit((uint8_t*)value, uint32_t(sizeof(T)));
		}
	};
}