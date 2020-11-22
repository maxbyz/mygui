/*!
	@file
	@author		Albert Semenov
	@date		04/2009
*/

#ifndef MYGUI_OGRE_TEXTURE_H_
#define MYGUI_OGRE_TEXTURE_H_

#include "MyGUI_Prerequest.h"
#include "MyGUI_ITexture.h"
#include "MyGUI_RenderFormat.h"

#include <OgreResource.h>
#include <OgreTexture.h>

namespace MyGUI
{

	struct OgreShaderInfo;

	class OgreTexture :
		public ITexture,
		public Ogre::ManualResourceLoader
	{
	public:
		OgreTexture(const std::string& _name, const std::string& _group);
		virtual ~OgreTexture();

		virtual const std::string& getName() const;

		virtual void createManual(int _width, int _height, TextureUsage _usage, PixelFormat _format);
		virtual void loadFromFile(const std::string& _filename);
		virtual void saveToFile(const std::string& _filename);
		virtual void setShader(const std::string& _shaderName);

		virtual void setInvalidateListener(ITextureInvalidateListener* _listener);

		virtual void destroy();

		virtual void* lock(TextureUsage _access);
		virtual void unlock();
		virtual bool isLocked();

		virtual int getWidth();
		virtual int getHeight();

		virtual PixelFormat getFormat()
		{
			return mOriginalFormat;
		}
		virtual TextureUsage getUsage()
		{
			return mOriginalUsage;
		}
		virtual size_t getNumElemBytes()
		{
			return mNumElemBytes;
		}

		virtual IRenderTarget* getRenderTarget();

		static Ogre::TextureUsage convertUsage(TextureUsage _usage);
		static Ogre::PixelFormat convertFormat(PixelFormat _format);
	/*internal:*/
		Ogre::TexturePtr getOgreTexture()
		{
			return mTexture;
		}
		void setOgreTexture(Ogre::TexturePtr _value)
		{
			mTexture = _value;
		}
		OgreShaderInfo* getShaderInfo() const
		{
			return mShaderInfo;
		}

	private:
		void setUsage(TextureUsage _usage);
		void setFormat(PixelFormat _format);
		void setFormatByOgreTexture();

		virtual void loadResource(Ogre::Resource* resource);

	private:
		Ogre::TexturePtr mTexture;
		OgreShaderInfo* mShaderInfo = nullptr;
		std::string mName;
		std::string mGroup;

		TextureUsage mOriginalUsage;
		PixelFormat mOriginalFormat;
		size_t mNumElemBytes;

		Ogre::PixelFormat mPixelFormat;
		Ogre::TextureUsage mUsage;

		ITextureInvalidateListener* mListener;
		IRenderTarget* mRenderTarget;
		Ogre::PixelBox mTmpData;
	};

} // namespace MyGUI

#endif // MYGUI_OGRE_TEXTURE_H_
