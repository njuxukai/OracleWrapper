#ifndef DB_WRAPPER_H_
#define DB_WRAPPER_H_


#include  <memory>
class DBWrapper
{
public:
	typedef std::shared_ptr<DBWrapper> SPtr;

	static SPtr CreateWrapper();
	virtual ~DBWrapper() {}
	virtual void submit(int task) = 0;
protected:
	DBWrapper() {}

private:
	DBWrapper(const DBWrapper&) = delete;
	DBWrapper& operator=(const DBWrapper&) = delete;
};

#endif