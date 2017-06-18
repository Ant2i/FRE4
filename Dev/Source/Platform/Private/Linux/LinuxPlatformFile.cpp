
namespace Platform
{

	class FileHandleLinux : public IFile
	{
		enum { READWRITE_SIZE = 1024 * 1024 };
		int32_t _handle;

		inline bool IsValid()
		{
			return _handle != -1;
		}

	public:
		FileHandleLinux(int32_t handle = -1)
			: _handle(handle)
		{
		}

		virtual void Release() override
		{
			delete this;
		}

		virtual ~FileHandleLinux()
		{
			close(_handle);
			_handle = -1;
		}

		virtual int64_t Pos() override
		{
			assert(IsValid());
			return lseek(_handle, 0, SEEK_CUR);
		}

		virtual bool Seek(int64_t pos) override
		{
			assert(IsValid());
			assert(pos >= 0);
			return lseek(_handle, pos, SEEK_SET) != -1;
		}

		virtual int64_t Read(char* dest, int64_t bytesToRead) override
		{
			int64_t readBytes = 0;

			assert(IsValid());
			while (bytesToRead)
			{
				assert(bytesToRead >= 0);
				int64_t batchSize = std::min((int64_t)READWRITE_SIZE, bytesToRead);
				assert(dest);
				ssize_t rb = read(_handle, dest, batchSize);
				if (rb != batchSize)
				{
					readBytes += rb;
					break;
				}
				dest += batchSize;
				bytesToRead -= batchSize;
				readBytes += rb;
			}
			return readBytes;
		}

		virtual int64_t Write(const char* src, int64_t bytesToWrite) override
		{
			int64_t writeBytes = 0;

			assert(IsValid());
			while (bytesToWrite)
			{
				assert(bytesToWrite >= 0);
				int64_t batchSize = std::min((int64_t)READWRITE_SIZE, bytesToWrite);
				assert(src);
				ssize_t wb = write(_handle, src, batchSize);
				if (wb != batchSize)
				{
					writeBytes += wb;
					break;
				}
				src += batchSize;
				bytesToWrite -= batchSize;
				writeBytes += wb;
			}
			return writeBytes;
		}
	};

	Path NormalizeFileName(const Path & fileName)
	{
		return fileName;
	}

	IFile * PlatformFile::OpenRead(const Path & fileName)
	{
		int32_t handle = open(ToUtf8(NormalizeFileName(fileName)).c_str(), O_RDONLY);
		if (handle != -1)
			return new FileHandleLinux(handle);
		return nullptr;
	}

	IFile * PlatformFile::OpenWrite(const Path & fileName, bool append, bool allowRead)
	{
		int Flags = O_CREAT;
		Flags |= append ? O_APPEND : O_TRUNC;
		Flags |= allowRead ? O_RDWR : O_WRONLY;

		int32_t handle = open(ToUtf8(NormalizeFileName(fileName)).c_str(), Flags, S_IRUSR | S_IWUSR);
		if (handle != -1)
			return new FileHandleLinux(handle);
		return nullptr;
	}

	Path PlatformFile::GetTemporaryFolderPath()
	{
		Path wchPath;
		const char * envPath = std::getenv("TMPDIR");
		if (envPath)
		{
			Utils::CStringToPath(envPath, wchPath);
		}
		else if (P_tmpdir)
		{
			Utils::CStringToPath(P_tmpdir, wchPath);
		}
		else
		{
			wchPath = L"/tmp";
		}

		return wchPath;
	}
}
