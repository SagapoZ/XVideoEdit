#include "XFilter.h"
#include <QMutex>
#include "XImagePro.h"
//继承接口类
class CXFilter :public XFilter
{
public:
	std::vector<XTask> tasks;
	QMutex mutex;
	//任务处理
	cv::Mat Filter(cv::Mat mat1, cv::Mat mat2)
	{
		mutex.lock();
		XImagePro p;
		//设置原图
		p.Set(mat1, mat2);
		for (int i = 0; i < tasks.size(); i++)
		{
			switch (tasks[i].type)
			{
			case XTASK_GAIN:
				//做亮度对比调整的任务
				p.Gain(tasks[i].para[0],
					tasks[i].para[1]
				);
				break;
			default:
				break;
			}
		}
		cv::Mat re = p.Get();
		mutex.unlock();
		return re;
	}
	void Add(XTask task) 
	{
		mutex.lock();
		tasks.push_back(task);
		mutex.unlock();
	}
	void Clear() 
	{
		mutex.lock();
		tasks.clear();
		mutex.unlock();
	}

};

XFilter *XFilter::Get()
{
	static CXFilter cx;
	return &cx;
}

XFilter::XFilter()
{
}


XFilter::~XFilter()
{
}
