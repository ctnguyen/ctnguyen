/*!
 * DataStream.h
 */
#ifndef DATASTREAM_H
#define DATASTREAM_H

#include <vector>
#include <iostream>

/*! Class define interface for DataStream
 */
class DataStream
{
public:

	// check if the stream is ended
	virtual bool isEnd() const = 0;

	// update the stream
	virtual void update() =0;

	virtual const std::vector<int>& getNewData() const = 0;	
};


/*! Class Simulate a Data Stream
 *  Data can be read from a text file
 *  Or generated randomly 
 */
class SampleDataStream : public DataStream
{
public:
	
	// build offline stream by reading a file
	SampleDataStream(const char* filename);
	
	// build offline stream by randomly generating numbers
	SampleDataStream(unsigned int N);

	// check if the stream is ended
	virtual bool isEnd() const;

	// update the stream
	virtual void update();

	virtual const std::vector<int>& getNewData() const;

	virtual ~SampleDataStream();

	const std::vector<int>& get_OfflineData() const;

	friend std::ostream& operator<<(std::ostream& os, const SampleDataStream& offlinestream);
private :

	size_t counter_;

	std::vector<int> offline_data_;

	std::vector<int> new_data_buffer;
	
	void write_to_stream(std::ostream& os) const;
};

//std::ostream& operator<<(std::ostream& os, const SampleDataStream& offlinestream);


#endif /* DATASTREAM_H */
