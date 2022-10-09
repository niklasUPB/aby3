
#include <cryptoTools/Common/CLP.h>

#include "cryptoTools/Common/BitIterator.h"
#include "cryptoTools/Common/Timer.h"
#include "cryptoTools/Crypto/PRNG.h"
#include <cryptoTools/Network/IOService.h>
#include <atomic>
#include "aby3-DB/DBServer.h"
#include <unordered_set>
#include <typeinfo>
#include <stdlib.h>

using namespace oc;

void print_all_of_SharedTabel(SharedTable T, int i, DBServer server[]);


void DB_Intersect(u32 rows = 100, u32 cols = 3, u32 intersect = 30)
{
	using namespace aby3;
	IOService ios;
	Session s01(ios, "127.0.0.1:50000", SessionMode::Server, "01");
	Session s10(ios, "127.0.0.1:50000", SessionMode::Client, "01");
	Session s02(ios, "127.0.0.1:50000", SessionMode::Server, "02");
	Session s20(ios, "127.0.0.1:50000", SessionMode::Client, "02");
	Session s12(ios, "127.0.0.1:50000", SessionMode::Server, "12");
	Session s21(ios, "127.0.0.1:50000", SessionMode::Client, "12");

	PRNG prng(oc::ZeroBlock);
	DBServer srvs[3];
	srvs[0].init(0, s02, s01, prng);
	srvs[1].init(1, s10, s12, prng);
	srvs[2].init(2, s21, s20, prng);
	// s01.mBase.get()->mGroup.get()->mSockets.front().mSocket

	// 80 bits;
	u32 hashSize = 80;

	auto keyBitCount = srvs[0].mKeyBitCount;
	std::vector<ColumnInfo>
		aCols = {ColumnInfo{"key", TypeID::IntID, keyBitCount}},
		bCols = {ColumnInfo{"key", TypeID::IntID, keyBitCount}},
		comCols = {ColumnInfo{"key", TypeID::IntID, keyBitCount}};

	for (u32 i = 1; i < cols; ++i)
	{
		// emplace_back adds element to end of container
		aCols.emplace_back("a" + std::to_string(i), TypeID::IntID, 32);
		bCols.emplace_back("b" + std::to_string(i), TypeID::IntID, 32);
		comCols.emplace_back("c" + std::to_string(i), TypeID::IntID, 32);
	}

	Table a(rows, aCols), b(rows, bCols), com(rows, comCols);

	for (u64 i = 0; i < rows; ++i)
	{
		auto out = (i >= intersect);
		for (u64 j = 0; j < 2; ++j)
		{
			a.mColumns[0].mData(i, j) = i + 1;
			b.mColumns[0].mData(i, j) = i + 1 + (rows * out);
			com.mColumns[0].mData(i, j) = i + 1 + (rows * out);
		}
	}

	for (u64 i = 1; i < cols; ++i)
	{
		for (u64 j = 0; j < rows; ++j)
		{
			a.mColumns[i].mData(j, 0) = rand() % 100;
			b.mColumns[i].mData(j, 0) = rand() % 100;
			com.mColumns[i].mData(j, 0) = rand() % 100;
		}
	}

	Timer t;

	bool failed = false;
	auto routine = [&](int i)
	{
		setThreadName("t0");
		t.setTimePoint("start");

		auto A = (i == 0) ? srvs[i].localInput(a) : srvs[i].remoteInput(0);
		auto B = (i == 0) ? srvs[i].localInput(b) : srvs[i].remoteInput(0);
		auto C = (i == 0) ? srvs[i].localInput(com) : srvs[i].remoteInput(0);

		if (i == 0)
			t.setTimePoint("inputs");

		if (i == 0)
			srvs[i].setTimer(t);

		std::vector<SharedTable::ColRef> First_Select_collumns;
		std::vector<SharedTable::ColRef> Second_Select_collumns;

		for (u64 i = 0; i < cols; ++i)
		{
			First_Select_collumns.emplace_back(SharedTable::ColRef(B, B.mColumns[i]));
		}
		for (u64 i = 1; i < cols; ++i)
		{
			First_Select_collumns.emplace_back(SharedTable::ColRef(A, A.mColumns[i]));
		}

		auto intermediate = srvs[i].join(SharedTable::ColRef(A, A.mColumns[0]), SharedTable::ColRef(B, B.mColumns[0]), First_Select_collumns);

		for (u64 i = 0; i < intermediate.mColumns.size(); ++i)
		{
			Second_Select_collumns.emplace_back(SharedTable::ColRef(intermediate, intermediate.mColumns[i]));
		}

		for (u64 i = 1; i < cols; ++i)
		{
			Second_Select_collumns.emplace_back(SharedTable::ColRef(C, C.mColumns[i]));
		}

		/*
		std::vector<SharedTable::ColRef>
		{
			SharedTable::ColRef(B,B.mColumns[0])  , SharedTable::ColRef(B,B.mColumns[1]),SharedTable::ColRef(B,B.mColumns[2])
		}  );
		*/

		auto end = srvs[i].join(SharedTable::ColRef(C, C.mColumns[0]), SharedTable::ColRef(intermediate, intermediate.mColumns[0]), Second_Select_collumns);

		/*

				auto C =srvs[i].join( SharedTable::ColRef(A,A.mColumns[0])  , SharedTable::ColRef(B,B.mColumns[0])  ,std::vector<SharedTable::ColRef>
				{
					SharedTable::ColRef(B,B.mColumns[0])  , SharedTable::ColRef(B,B.mColumns[1]),SharedTable::ColRef(B,B.mColumns[2])
				}  );

		*/
		if (i == 0)
			t.setTimePoint("intersect");

		if (intermediate.rows())
		{
			if (i == 0)
				std::cout << "A" << std::endl;
			print_all_of_SharedTabel(A, i, srvs);
			if (i == 0)
				std::cout << "B" << std::endl;
			print_all_of_SharedTabel(B, i, srvs);
			if (i == 0)
				std::cout << "C" << std::endl;
			print_all_of_SharedTabel(C, i, srvs);
			if (i == 0)
				std::cout << "intermediate" << std::endl;
			print_all_of_SharedTabel(intermediate, i, srvs);
			if (i == 0)
				std::cout << "end" << std::endl;
			print_all_of_SharedTabel(end, i, srvs);
			if (i == 0)
			{

				t.setTimePoint("reveal");
			}
		}
		else
		{
			failed = true;
		}
	};

	auto t0 = std::thread(routine, 0);
	auto t1 = std::thread(routine, 1);
	routine(2);

	t0.join();
	t1.join();

	auto comm0 = (srvs[0].mRt.mComm.mNext.getTotalDataSent() + srvs[0].mRt.mComm.mPrev.getTotalDataSent());
	auto comm1 = (srvs[1].mRt.mComm.mNext.getTotalDataSent() + srvs[1].mRt.mComm.mPrev.getTotalDataSent());
	auto comm2 = (srvs[2].mRt.mComm.mNext.getTotalDataSent() + srvs[2].mRt.mComm.mPrev.getTotalDataSent());
	std::cout << "n = " << rows << "   " << comm0 + comm1 + comm2 << "\n"
			  << t << std::endl;

	if (failed)
	{
		std::cout << "bad intersection" << std::endl;
		throw std::runtime_error("");
	}
}

void print_all_of_SharedTabel(SharedTable T, int i, DBServer server[])
{
	for (u64 index = 0; index < T.mColumns.size(); ++index)
	{

		aby3::i64Matrix t(T.mColumns[index].rows(), T.mColumns[index].i64Cols());
		server[i].mEnc.revealAll(server[i].mRt.mComm, T.mColumns[index], t);
		if (i == 0)
		{
			std::cout << T.mColumns[index].mName << std::endl;
			std::cout << t << std::endl;
			std::cout << std::endl;
			std::cout << std::endl;
		}
	}
}
void print_all_of_Table(Table b)
{
	int index = 0;
	while (index < b.mColumns.size())
	{
		std::cout << "'''''''" << std::endl;
		std::cout << b.mColumns[index].mName << std::endl;
		std::cout << b.mColumns[index].mData << std::endl;
		index++;
	}
}

void DB_compare_test()
{

	IOService ios;
	Session s01(ios, "127.0.0.1", SessionMode::Server, "01");
	Session s10(ios, "127.0.0.1", SessionMode::Client, "01");
	Session s02(ios, "127.0.0.1", SessionMode::Server, "02");
	Session s20(ios, "127.0.0.1", SessionMode::Client, "02");
	Session s12(ios, "127.0.0.1", SessionMode::Server, "12");
	Session s21(ios, "127.0.0.1", SessionMode::Client, "12");

	PRNG prng(OneBlock);
	DBServer srvs[3];
	srvs[0].init(0, s02, s01, prng);
	srvs[1].init(1, s10, s12, prng);
	srvs[2].init(2, s21, s20, prng);

	// 80 bits;
	auto keyBitCount = srvs[0].mKeyBitCount;
	u32 rows = 5;

	// b.mColumns[0].resize(rows, (srvs[0].mKeyBitCount + 63) / 64);
	Table b(rows, {ColumnInfo{"key", TypeID::IntID, keyBitCount}, ColumnInfo{"data", TypeID::IntID, 64}, ColumnInfo{"data2", TypeID::IntID, 64}});

	b.mColumns[0].mData.setZero();

	std::vector<u8> expIntersection(rows, 0);

	for (u64 i = 0; i < rows; ++i)
	{
		expIntersection[i] = prng.get<bool>();
		u8 *d = (u8 *)b.mColumns[0].mData.row(i).data();
		auto size = b.mColumns[0].mData.cols();
		prng.get(d, size);
	}

	print_all_of_Table(b);

	bool failed = false;

	auto routine = [&](int i)
	{
		SharedTable B, C;

		if (i == 0)
			B = srvs[i].localInput(b);
		else
			B = srvs[i].remoteInput(0);

		C.mColumns.resize(4);
		C.mColumns[0].mShares = B.mColumns[0].mShares;
		C.mColumns[0].mName = B.mColumns[0].mName;
		C.mColumns[0].mType = B.mColumns[0].mType;
		C.mColumns[0].mBitCount = B.mColumns[0].mBitCount;

		C.mColumns[1].mShares = B.mColumns[1].mShares;
		C.mColumns[1].mName = B.mColumns[1].mName;
		C.mColumns[1].mType = B.mColumns[1].mType;
		C.mColumns[1].mBitCount = B.mColumns[1].mBitCount;

		C.mColumns[2].mShares = B.mColumns[1].mShares;
		C.mColumns[2].mName = "add";
		C.mColumns[2].mType = B.mColumns[1].mType;
		C.mColumns[2].mBitCount = B.mColumns[1].mBitCount;

		C.mColumns[3].mShares = B.mColumns[2].mShares;
		C.mColumns[3].mName = B.mColumns[2].mName;
		;
		C.mColumns[3].mType = B.mColumns[2].mType;
		C.mColumns[3].mBitCount = B.mColumns[2].mBitCount;

		C.mColumns[0].mShares[0].setZero();
		C.mColumns[0].mShares[1].setZero();
		C.mColumns[1].mShares[0].setZero();
		C.mColumns[1].mShares[1].setZero();
		C.mColumns[2].mShares[0].setZero();
		C.mColumns[2].mShares[1].setZero();
		C.mColumns[3].mShares[0].setZero();
		C.mColumns[3].mShares[1].setZero();

		// print_all_of_SharedTabel(C,i,srvs );

		aby3::PackedBin plainFlags(B.rows(), 1);
		SharedTable A = B;
		osuCrypto::SharedTable::ColRef leftJoin = A["key"];
		osuCrypto::SharedTable::ColRef rightJoin = B["key"];
		std::vector<SharedColumn *> outCols{&C["data"].mCol, &C["add"].mCol, &C["data2"].mCol},
			leftCircuitInputs{&leftJoin.mCol},
			rightCircuitInputs{&rightJoin.mCol, &B["data"].mCol, &B["data2"].mCol};
		SelectQuery query;
		SelectBundle key = query.joinOn(leftJoin, rightJoin);
		query.addOutput("key", key);

		auto dd = query.addInput(B["data"]);
		auto ff = query.addInput(B["data2"]);

		query.addOutput("data", dd);
		query.addOutput("add", dd + ff);
		query.addOutput("data2", dd * ff);
		if (i < 2)
		{
			// von 0 und 1

			auto selectBytes = 0ull;
			for (auto &c : rightCircuitInputs)
				selectBytes += (c->getBitCount() + 7) / 8;

			std::array<Matrix<u8>, 3> selects2;

			selects2[0].resize(rows, selectBytes);
			selects2[1].resize(rows, selectBytes);
			selects2[2].resize(rows, selectBytes);

			// von 0
			if (i == 0) // muss ausgeführt werden
			{
				for (u64 j = 0; j < rows; ++j)
				{
					if (expIntersection[j])
					{
						u8 idx = prng.get<u8>() % 3;

						auto dest = selects2[idx][j].data();
						auto src = b.mColumns[0].mData.row(j).data();
						auto size = (b.mColumns[0].getBitCount() + 7) / 8;

						if (selectBytes != size + 2 * C["data"].mCol.getByteCount())
							throw RTE_LOC;

						// memcpy(dest, src, size);
						// dest += size;
						memcpy(dest, src, size);
						dest += size;
						((u64 *)dest)[0] = j;
						((u64 *)dest)[1] = j;
					}
				}
			}
			auto intersectionFlags = srvs[i].compare(leftCircuitInputs, rightCircuitInputs, outCols, query, selects2);
			// srvs[i].mEnc.revealAll(srvs[i].mRt.noDependencies(), intersectionFlags, plainFlags).get();
			// BitIterator iter((u8*)plainFlags.mData.data(), 0);
			/*
			//auto stride = C.mColumns[0].i64Cols();
			aby3::i64Matrix c0(C.rows(), stride), c1(C.rows(), 1), c2(C.rows(), 1);
			srvs[i].mEnc.revealAll(srvs[i].mRt.noDependencies(), C.mColumns[0], c0).get();
			srvs[i].mEnc.revealAll(srvs[i].mRt.noDependencies(), C.mColumns[1], c1).get();
			srvs[i].mEnc.revealAll(srvs[i].mRt.noDependencies(), C.mColumns[2], c2).get();

			if(false){
			std:: cout << "'''''''" << std::endl;
			std:: cout << "Oben" << std::endl;
			std:: cout << c0 << std::endl;
			std:: cout << "'''''''" << std::endl;
			std:: cout << c1 << std::endl;
			std:: cout << "'''''''" << std::endl;
			std:: cout << c2 << std::endl;
			std:: cout << "'''''''" << std::endl;
			}

			//ostreamLock o(std::cout);
			for (u64 j = 0; j < rows; ++j)
			{

				//o << "out[" << j << "] = "
				//    << hexString((u8*)c0.row(j).data(), c0.cols() * sizeof(u64)) << " "
				//    << hexString((u8*)c1.row(j).data(), c1.cols() * sizeof(u64)) << " " << int(*iter) << std::endl;;

				if (*iter != expIntersection[j])
				{
					failed = true;

				}
				else
				{
					//for (u64 k = 0; k < stride; ++k)
					//{
					//    if (c0(j, k) != *iter * b.mColumns[0].mData(j, k))
					//        failed = true;
					//}


					if (c1(j, 0) != *iter * j)
						failed = true;

					if (c2(j, 0) != *iter * j * 2)
						failed = true;
				}

				++iter;
			}*/
		}

		// von 2
		else
		{

			auto intersectionFlags = srvs[i].compare(leftCircuitInputs, rightCircuitInputs, outCols, query, {});

			// srvs[i].mEnc.revealAll(srvs[i].mRt.noDependencies(), intersectionFlags, plainFlags).get();

			// aby3::i64Matrix c(C.rows(), C.mColumns[0].i64Cols()), c1(C.rows(), 1);
			// srvs[i].mEnc.revealAll(srvs[i].mRt.noDependencies(), C.mColumns[0], c).get();
			// srvs[i].mEnc.revealAll(srvs[i].mRt.noDependencies(), C.mColumns[1], c1).get();
			// srvs[i].mEnc.revealAll(srvs[i].mRt.noDependencies(), C.mColumns[2], c1).get();
		}
		print_all_of_SharedTabel(C, i, srvs);
	};

	auto t0 = std::thread(routine, 0);
	auto t1 = std::thread(routine, 1);

	routine(2);
	t0.join();
	t1.join();

	if (failed)
	{
		std::cout << "failed" << std::endl;
		throw RTE_LOC;
	}
}
void use_case2(u32 rows = 10,  u32 intersect = 5)
{
	u32 cols = 2;
	using namespace aby3;
	IOService ios;
	Session s01(ios, "127.0.0.1:50000", SessionMode::Server, "01");
	Session s10(ios, "127.0.0.1:50000", SessionMode::Client, "01");
	Session s02(ios, "127.0.0.1:50000", SessionMode::Server, "02");
	Session s20(ios, "127.0.0.1:50000", SessionMode::Client, "02");
	Session s12(ios, "127.0.0.1:50000", SessionMode::Server, "12");
	Session s21(ios, "127.0.0.1:50000", SessionMode::Client, "12");

	PRNG prng(oc::ZeroBlock);
	DBServer srvs[3];
	srvs[0].init(0, s02, s01, prng);
	srvs[1].init(1, s10, s12, prng);
	srvs[2].init(2, s21, s20, prng);
	// s01.mBase.get()->mGroup.get()->mSockets.front().mSocket

	// 80 bits;
	u32 hashSize = 80;

	auto keyBitCount = srvs[0].mKeyBitCount;
	std::vector<ColumnInfo>
		aCols = {ColumnInfo{"key", TypeID::IntID, keyBitCount}},
		bCols = {ColumnInfo{"key", TypeID::IntID, keyBitCount}},
		a_zeroCols = {ColumnInfo{"key", TypeID::IntID, keyBitCount}},
		b_zeroCols = {ColumnInfo{"key", TypeID::IntID, keyBitCount}},
		a_oneCols  =  {ColumnInfo{"key", TypeID::IntID, keyBitCount}},
		b_oneCols  =  {ColumnInfo{"key", TypeID::IntID, keyBitCount}};
		

	for (u32 i = 1; i < cols; ++i)
	{
		// emplace_back adds element to end of container
		aCols.emplace_back("a" + std::to_string(i), TypeID::IntID,1 );
		bCols.emplace_back("b" + std::to_string(i), TypeID::IntID,1 );
		a_zeroCols.emplace_back("a" + std::to_string(i), TypeID::IntID,1 );
		b_zeroCols.emplace_back("b" + std::to_string(i), TypeID::IntID,1 );
		a_oneCols.emplace_back("a" + std::to_string(i), TypeID::IntID,1 );
		b_oneCols.emplace_back("b" + std::to_string(i), TypeID::IntID,1 );

		
	}
	
	Table a(rows, aCols), b(rows, bCols);

	for (u64 i = 0; i < rows; ++i)
	{
		auto out = (i >= intersect);
		for (u64 j = 0; j < 2; ++j)
		{
			a.mColumns[0].mData(i, j) = i + 1;
			b.mColumns[0].mData(i, j) = i + 1 + (rows * out);
			
		}
	}
	srandom(11132);
	for (u64 i = 1; i < cols; ++i)
	{
		for (u64 j = 0; j < rows; ++j)
		{
			int k = 1;
			a.mColumns[i].mData(j, 0) = rand() %2;
			b.mColumns[i].mData(j, 0) = rand() %2 ;
		}
	}
		int zeros = 0;
		int ones = 0;
		for (u64 j = 0; j < rows; ++j){
			if (a.mColumns[1].mData(j,0) == 0) zeros =  zeros +1;
			else
			{
				ones = ones+1;
			}	
		}
		Table a_with_ones(ones, a_oneCols) ;
		int ones_index =0;
		int zeros_index =0;
		Table a_with_zeros(zeros, a_zeroCols );
		for (u64 j = 0; j < rows; ++j){
			if(a.mColumns[1].mData(j,0) == 0) {
				a_with_zeros.mColumns[0].mData(zeros_index,0) = a.mColumns[0].mData(j,0);
				a_with_zeros.mColumns[0].mData(zeros_index,1) = a.mColumns[0].mData(j,1);
				a_with_zeros.mColumns[1].mData(zeros_index,0) = 0;
				zeros_index = zeros_index +1;
			} 
			else{
				a_with_ones .mColumns[0].mData(ones_index,0) = a.mColumns[0].mData(j,0);
				a_with_ones.mColumns[0].mData(ones_index,1) = a.mColumns[0].mData(j,1);
				a_with_ones.mColumns[1].mData(ones_index,0) = 1;
				ones_index = ones_index +1;
			}
		}
		zeros = 0;
		ones = 0;
		for (u64 j = 0; j < rows; ++j){
			if (b.mColumns[1].mData(j,0) == 0) zeros =  zeros +1;
			else
			{
				ones = ones+1;
			}	
		}
		Table b_with_ones(ones, b_oneCols) ;
		ones_index =0;
		zeros_index =0;
		Table b_with_zeros(zeros, b_zeroCols );
		for (u64 j = 0; j < rows; ++j){
			if(b.mColumns[1].mData(j,0) == 0) {
				b_with_zeros.mColumns[0].mData(zeros_index,0) = b.mColumns[0].mData(j,0);
				b_with_zeros.mColumns[0].mData(zeros_index,1) = b.mColumns[0].mData(j,1);
				b_with_zeros.mColumns[1].mData(zeros_index,0) = 0;
				zeros_index = zeros_index +1;
			} 
			else{
				b_with_ones .mColumns[0].mData(ones_index,0) = b.mColumns[0].mData(j,0);
				b_with_ones.mColumns[0].mData(ones_index,1) = b.mColumns[0].mData(j,1);
				b_with_ones.mColumns[1].mData(ones_index,0) = 1;
				ones_index = ones_index +1;
			}
		}
	
	Timer t;
	bool failed = false;
	print_all_of_Table(a);
	print_all_of_Table(b);
	auto getIntermediate =[&] (int i, int filter){
		SharedTable A;
		SharedTable B;
		if (filter == 1) {
			A = (i == 0) ? srvs[i].localInput(a_with_ones) : srvs[i].remoteInput(0);
			B = (i == 1) ? srvs[i].localInput(b_with_ones) : srvs[i].remoteInput(1);
			
		}else{
			B = (i == 1) ? srvs[i].localInput(b_with_zeros ) : srvs[i].remoteInput(1);
			A = (i == 0) ? srvs[i].localInput(a_with_zeros) : srvs[i].remoteInput(0);
		}
		std::vector<SharedTable::ColRef>  First_Select_collumns; 
		First_Select_collumns.emplace_back(SharedTable::ColRef(B , B.mColumns[0]) );
		First_Select_collumns.emplace_back(SharedTable::ColRef(B , B.mColumns[1]) );
		First_Select_collumns.emplace_back(SharedTable::ColRef(A , A.mColumns[1]) );
		return srvs[i].join( SharedTable::ColRef(  A , A.mColumns[0]) , SharedTable::ColRef( B, B.mColumns[0]  ), First_Select_collumns);

	};



	auto routine = [&](int i, int filter)
	{
		setThreadName("t0");
		t.setTimePoint("start");
		SharedTable intermediateOne = getIntermediate(i,0);
		t.setTimePoint("first_intermediate");
		SharedTable intermediateZero = getIntermediate(i,1);
		t.setTimePoint("second_intermediate");
		//print_all_of_SharedTabel(intermediateZero,i,srvs);
		//print_all_of_SharedTabel(intermediateOne,i,srvs);
		SharedTable UNION;
		std::vector<SharedTable::ColRef>  SelectOnes; 
		SelectOnes.emplace_back(SharedTable::ColRef( intermediateOne , intermediateOne.mColumns[0]) );
		SelectOnes.emplace_back(SharedTable::ColRef( intermediateOne , intermediateOne.mColumns[1]) );
		SelectOnes.emplace_back(SharedTable::ColRef( intermediateOne , intermediateOne.mColumns[2]) );
		std::vector<SharedTable::ColRef>  SelectZeros; 
		SelectZeros.emplace_back(SharedTable::ColRef( intermediateZero , intermediateZero.mColumns[0]) );
		SelectZeros.emplace_back(SharedTable::ColRef( intermediateZero , intermediateZero.mColumns[1]) );
		SelectZeros.emplace_back(SharedTable::ColRef( intermediateZero , intermediateZero.mColumns[2]) );
		UNION = srvs[i].rightUnion(SharedTable::ColRef( intermediateZero, intermediateZero.mColumns[0] ),
		SharedTable::ColRef( intermediateOne, intermediateOne.mColumns[0]),  SelectZeros,SelectOnes  );
		t.setTimePoint("UNION");
		
		print_all_of_SharedTabel( UNION,i,srvs );
		
	};


	

	auto t0 = std::thread(routine, 0,1);
	auto t1 = std::thread(routine, 1,1);
	routine(2,1);
	t0.join();
	t1.join();
	auto comm0 = (srvs[0].mRt.mComm.mNext.getTotalDataSent() + srvs[0].mRt.mComm.mPrev.getTotalDataSent());
	auto comm1 = (srvs[1].mRt.mComm.mNext.getTotalDataSent() + srvs[1].mRt.mComm.mPrev.getTotalDataSent());
	auto comm2 = (srvs[2].mRt.mComm.mNext.getTotalDataSent() + srvs[2].mRt.mComm.mPrev.getTotalDataSent());
	std::cout << "n = " << rows << "   " << comm0 + comm1 + comm2 << "\n" << t << std::endl;


}

void compare_random(u32 rows = 20, u32 cols = 2, u32 intersect = 30)
{

	using namespace aby3;
	IOService ios;
	Session s01(ios, "127.0.0.1:50000", SessionMode::Server, "01");
	Session s10(ios, "127.0.0.1:50000", SessionMode::Client, "01");
	Session s02(ios, "127.0.0.1:50000", SessionMode::Server, "02");
	Session s20(ios, "127.0.0.1:50000", SessionMode::Client, "02");
	Session s12(ios, "127.0.0.1:50000", SessionMode::Server, "12");
	Session s21(ios, "127.0.0.1:50000", SessionMode::Client, "12");

	PRNG prng(oc::ZeroBlock);
	DBServer srvs[3];
	srvs[0].init(0, s02, s01, prng);
	srvs[1].init(1, s10, s12, prng);
	srvs[2].init(2, s21, s20, prng);
	// s01.mBase.get()->mGroup.get()->mSockets.front().mSocket

	// 80 bits;
	u32 hashSize = 80;

	auto keyBitCount = srvs[0].mKeyBitCount;
	std::vector<ColumnInfo>
		aCols = {ColumnInfo{"key", TypeID::IntID, keyBitCount}},
		bCols = {ColumnInfo{"key", TypeID::IntID, keyBitCount}},
		comCols = {ColumnInfo{"key", TypeID::IntID, keyBitCount}};

	for (u32 i = 1; i < cols; ++i)
	{
		// emplace_back adds element to end of container
		aCols.emplace_back("a" + std::to_string(i), TypeID::IntID,64 );
		bCols.emplace_back("b" + std::to_string(i), TypeID::IntID,64 );
		comCols.emplace_back("c" + std::to_string(i), TypeID::IntID,64 );
	}
	
	Table a(rows, aCols), b(rows, bCols), com(rows, comCols);

	for (u64 i = 0; i < rows; ++i)
	{
		auto out = (i >= intersect);
		for (u64 j = 0; j < 2; ++j)
		{
			a.mColumns[0].mData(i, j) = i + 1;
			b.mColumns[0].mData(i, j) = i + 1 + (rows * out);
			com.mColumns[0].mData(i, j) = i + 1 + (rows * out);
		}
	}
	srandom(11011);
	for (u64 i = 1; i < cols; ++i)
	{
		for (u64 j = 0; j < rows; ++j)
		{
			int k = 1;
			if(j %2 == 0) k = 1;
			a.mColumns[i].mData(j, 0) = ((rand() %1000)) *k;
			b.mColumns[i].mData(j, 0) = (rand() %1000 );
			com.mColumns[i].mData(j, 0) = (rand() %1000 );
		}
	}
	
	Timer t;
	bool failed = false;
	auto routine = [&](int i)
	{
		setThreadName("t0");
		t.setTimePoint("start");

		auto A = (i == 0) ? srvs[i].localInput(a) : srvs[i].remoteInput(0);
		auto B = (i == 0) ? srvs[i].localInput(b) : srvs[i].remoteInput(0);
		auto C = (i == 0) ? srvs[i].localInput(com) : srvs[i].remoteInput(0);
		print_all_of_SharedTabel(A, i, srvs);
		print_all_of_SharedTabel(B, i, srvs);
		print_all_of_SharedTabel(C, i, srvs);
		if (i == 0)
			t.setTimePoint("inputs");

		if (i == 0)
			srvs[i].setTimer(t);

		SelectQuery select;
		auto REQUIRED = select.joinOn(A["key"], C["key"]);
		auto a1 = select.addInput(A["a1"]);
		auto c1 = select.addInput(C["c1"]);
		auto larger = c1 < a1;
		select.addOutput("a1", a1);
		select.addOutput("c1", c1);
		select.addOutput("larger", larger);

		auto intersection = srvs[i].joinImpl(select);
		print_all_of_SharedTabel(intersection, i, srvs);
	};
	auto t0 = std::thread(routine, 0);
	auto t1 = std::thread(routine, 1);
	routine(2);
	t0.join();
	t1.join();
}
//copiert von intersect
void DB_test(u32 rows = 100, u32 cols = 3, bool sum = true)
{
	using namespace aby3;
	IOService ios;
	Session s01(ios, "127.0.0.1", SessionMode::Server, "01");
	Session s10(ios, "127.0.0.1", SessionMode::Client, "01");
	Session s02(ios, "127.0.0.1", SessionMode::Server, "02");
	Session s20(ios, "127.0.0.1", SessionMode::Client, "02");
	Session s12(ios, "127.0.0.1", SessionMode::Server, "12");
	Session s21(ios, "127.0.0.1", SessionMode::Client, "12");

	
	PRNG prng(oc::ZeroBlock);
	DBServer srvs[3];
	srvs[0].init(0, s02, s01, prng);
	srvs[1].init(1, s10, s12, prng);
	srvs[2].init(2, s21, s20, prng);


	// 80 bits;
	u32 hashSize = 80;

	auto keyBitCount = srvs[0].mKeyBitCount;
	std::vector<ColumnInfo>
		aCols = { ColumnInfo{ "key", TypeID::IntID, keyBitCount } },
		bCols = { ColumnInfo{ "key", TypeID::IntID, keyBitCount } };

	for (u32 i = 0; i < cols; ++i)
	{
		//aCols.emplace_back("a" + std::to_string(i), TypeID::IntID, 32);
		bCols.emplace_back("b" + std::to_string(i), TypeID::IntID, 32);
	}

	Table a(rows, aCols)
		, b(rows, bCols);
	auto intersectionSize = (rows + 1) / 2;


	for (u64 i = 0; i < rows; ++i)
	{
		auto out = (i >= intersectionSize);
		for (u64 j = 0; j < a.mColumns[0].mData.cols(); ++j)
		{
			a.mColumns[0].mData(i, j) = i + 1;
			b.mColumns[0].mData(i, j) = i + 1 + (rows * out);
		}
	}

	Timer t;

	bool failed = false;
	auto routine = [&](int i) {
		setThreadName("t0");
		t.setTimePoint("start");


		auto A = (i == 0) ? srvs[i].localInput(a) : srvs[i].remoteInput(0);
		auto B = (i == 0) ? srvs[i].localInput(b) : srvs[i].remoteInput(0);

		if (i == 0)
			t.setTimePoint("inputs");

		if (i == 0)
			srvs[i].setTimer(t);



		SelectQuery query;
		query.noReveal("r");
		auto aKey = query.joinOn(A["key"], B["key"]);
		query.addOutput("key", aKey);

		for (u32 i = 0; i < cols; ++i)
		{
			//query.addOutput("a" + std::to_string(i), query.addInput(A["a" + std::to_string(i)]));
			query.addOutput("b" + std::to_string(i), query.addInput(B["b" + std::to_string(i)]));
		}

		auto C = srvs[i].joinImpl(query);

		if (i == 0)
			t.setTimePoint("intersect");


		if (sum)
		{

			Sh3BinaryEvaluator eval;

			BetaLibrary lib;
			BetaCircuit* cir = lib.int_int_add(64, 64, 64);

			auto task = srvs[i].mRt.noDependencies();

			sbMatrix AA(C.rows(), 64), BB(C.rows(), 64), CC(C.rows(), 64);
			task = eval.asyncEvaluate(task, cir, srvs[i].mEnc.mShareGen, { &AA, &BB }, { &CC });
			
			Sh3Encryptor enc;
			if (i == 0)
			{
				i64Matrix m(C.rows(), 1);
				enc.reveal(task, CC, m).get();
				
			}
			else
				enc.reveal(task, 0, CC).get();


			if (i == 0)
				t.setTimePoint("sum");
		}
		else if (C.rows())
		{
			aby3::i64Matrix c(C.mColumns[0].rows(), C.mColumns[0].i64Cols());
			srvs[i].mEnc.revealAll(srvs[i].mRt.mComm, C.mColumns[0], c);

			if (i == 0)
				t.setTimePoint("reveal");
		}
		else
		{
			failed = true;
		}
		//std::cout << t << std::endl << srvs[i].getTimer() << std::endl;
	};

	auto t0 = std::thread(routine, 0);
	auto t1 = std::thread(routine, 1);
	routine(2);

	t0.join();
	t1.join();

	auto comm0 = (srvs[0].mRt.mComm.mNext.getTotalDataSent() + srvs[0].mRt.mComm.mPrev.getTotalDataSent());
	auto comm1 = (srvs[1].mRt.mComm.mNext.getTotalDataSent() + srvs[1].mRt.mComm.mPrev.getTotalDataSent());
	auto comm2 = (srvs[2].mRt.mComm.mNext.getTotalDataSent() + srvs[2].mRt.mComm.mPrev.getTotalDataSent());
	std::cout << "n = " << rows << "   " << comm0 + comm1 + comm2 << "\n" << t << std::endl;

	if (failed)
	{
		std::cout << "bad intersection" << std::endl;
		throw std::runtime_error("");
	}
}
void DB_threat(u32 rows=4, u32 setCount=12)
{
	using namespace aby3;

	IOService ios;
	Session s01(ios, "127.0.0.1", SessionMode::Server, "01");
	Session s10(ios, "127.0.0.1", SessionMode::Client, "01");
	Session s02(ios, "127.0.0.1", SessionMode::Server, "02");
	Session s20(ios, "127.0.0.1", SessionMode::Client, "02");
	Session s12(ios, "127.0.0.1", SessionMode::Server, "12");
	Session s21(ios, "127.0.0.1", SessionMode::Client, "12");


	PRNG prng(oc::ZeroBlock);
	DBServer srvs[3];
	srvs[0].init(0, s02, s01, prng);
	srvs[1].init(1, s10, s12, prng);
	srvs[2].init(2, s21, s20, prng);


	// 80 bits;
	u32 hashSize = 80;



	auto keyBitCount = srvs[0].mKeyBitCount;
	std::vector<ColumnInfo>
		aCols = { ColumnInfo{ "key", TypeID::IntID, keyBitCount } },
		bCols = { ColumnInfo{ "key", TypeID::IntID, keyBitCount } };

	Table a(rows, aCols)
		, b(rows, bCols);
	auto intersectionSize = (rows + 1) / 2;


	for (u64 i = 0; i < rows; ++i)
	{
		auto out = (i >= intersectionSize);
		for (u64 j = 0; j < a.mColumns[0].mData.cols(); ++j)
		{
			a.mColumns[0].mData(i, j) = i + 1;
			b.mColumns[0].mData(i, j) = i + 1 + (rows * out);
		}
	}

	Timer t;
	
	bool failed = false;
	auto routine = [&](int i) {
		print_all_of_Table(a);
		print_all_of_Table(b);
		setThreadName("t0");
		if (i == 0)
			t.setTimePoint("start");

		BetaLibrary lib;
		BetaCircuit * cir = lib.int_int_add(64, 64, 64);

		auto A = (i == 0) ? srvs[i].localInput(a) : srvs[i].remoteInput(0);
		auto B = (i == 0) ? srvs[i].localInput(b) : srvs[i].remoteInput(0);
		SharedTable C;
		
		if (i == 0)
			t.setTimePoint("inputs");

		//if (i == 0)
		//	srvs[i].setTimer(t);

		auto ss = setCount;
		while (ss > 1)
		{

			int loops = ss / 2;

			for (u64 j = 0; j < loops; ++j)
			{
				C = srvs[i].rightUnion(A["key"], B["key"], { A["key"] }, { B["key"] });
			}

			A = C;
			B = C;
			ss -= loops;
		}

		if (i == 0)
			t.setTimePoint("union");

		Sh3BinaryEvaluator eval;


		auto task = srvs[i].mRt.noDependencies();
		print_all_of_SharedTabel(A,i,srvs);
		print_all_of_SharedTabel(B,i,srvs);
		print_all_of_SharedTabel(C,i,srvs);
		sbMatrix AA(C.rows(), 64), BB(C.rows(), 64), CC(C.rows(), 64);
		
		task = eval.asyncEvaluate(task, cir, srvs[i].mEnc.mShareGen, { &AA, &BB }, { &CC });
		task = eval.asyncEvaluate(task, cir, srvs[i].mEnc.mShareGen, { &AA, &BB }, { &CC });
		
		
		task.get();
		/*
		Sh3Encryptor enc;
			if (i == 0)
			{
				i64Matrix m(C.rows(), 2);
				enc.reveal(task, CC, m).get();
				std::cout << m << std::endl;
			}
			else
				enc.reveal(task, 0, CC).get();


		*/
	
		if (i == 0)
			t.setTimePoint("done");
		if (C.rows())
		{
			aby3::i64Matrix c(C.mColumns[0].rows(), C.mColumns[0].i64Cols());
			srvs[i].mEnc.revealAll(srvs[i].mRt.mComm, C.mColumns[0], c);
			std::cout << c << std::endl;

			if (i == 0)
				t.setTimePoint("reveal");
		}
		else
		{
			failed = true;
		}
		//std::cout << t << std::endl << srvs[i].getTimer() << std::endl;
	};

	auto t0 = std::thread(routine, 0);
	auto t1 = std::thread(routine, 1);
	routine(2);

	t0.join();
	t1.join();

	auto comm0 = (srvs[0].mRt.mComm.mNext.getTotalDataSent() + srvs[0].mRt.mComm.mPrev.getTotalDataSent());
	auto comm1 = (srvs[1].mRt.mComm.mNext.getTotalDataSent() + srvs[1].mRt.mComm.mPrev.getTotalDataSent());
	auto comm2 = (srvs[2].mRt.mComm.mNext.getTotalDataSent() + srvs[2].mRt.mComm.mPrev.getTotalDataSent());
	std::cout << "n = " << rows << "   " << comm0 + comm1 + comm2 << "\n" << t << std::endl;

	if (failed)
	{
		std::cout << "bad intersection" << std::endl;
		throw std::runtime_error("");
	}
}
void eric(int n)
{


    IOService ios;
    Session s01(ios, "127.0.0.1", SessionMode::Server, "01");
    Session s10(ios, "127.0.0.1", SessionMode::Client, "01");
    Session s02(ios, "127.0.0.1", SessionMode::Server, "02");
    Session s20(ios, "127.0.0.1", SessionMode::Client, "02");
    Session s12(ios, "127.0.0.1", SessionMode::Server, "12");
    Session s21(ios, "127.0.0.1", SessionMode::Client, "12");


    PRNG prng(OneBlock );
    DBServer srvs[3];
    srvs[0].init(0, s02, s01, prng);
    srvs[1].init(1, s10, s12, prng);
    srvs[2].init(2, s21, s20, prng);



    auto keyBitCount = srvs[0].mKeyBitCount;

    std::vector<ColumnInfo> voterSchema{
        //ColumnInfo{ "NA", TypeID::IntID, keyBitCount },
        //ColumnInfo{ "AD", TypeID::IntID, keyBitCount },
        ColumnInfo{ "DL", TypeID::IntID, keyBitCount }
    }, 
    dvmSchema{
        ColumnInfo{ "NA", TypeID::IntID, keyBitCount },
        ColumnInfo{ "AD", TypeID::IntID, 24 },
        ColumnInfo{ "DL", TypeID::IntID, keyBitCount },
        //ColumnInfo{ "DOB", TypeID::IntID, keyBitCount },
        ColumnInfo{ "SSN", TypeID::IntID, keyBitCount }
    }/*,
    stateSchema{
        ColumnInfo{ "NA_vote", TypeID::IntID, keyBitCount },
        ColumnInfo{ "AD_vote", TypeID::IntID, keyBitCount },
        ColumnInfo{ "NA_dmv", TypeID::IntID, keyBitCount },
        ColumnInfo{ "AD_dvm", TypeID::IntID, keyBitCount },
        ColumnInfo{ "DL", TypeID::IntID, keyBitCount },
        ColumnInfo{ "DOB", TypeID::IntID, keyBitCount },
        ColumnInfo{ "SSN", TypeID::IntID, keyBitCount },
        ColumnInfo{ "Reg", TypeID::IntID, 1 }
    },
    uspsData{
        ColumnInfo{ "NA", TypeID::IntID, keyBitCount },
        ColumnInfo{ "NA_new", TypeID::IntID, keyBitCount },
        ColumnInfo{ "AD_new", TypeID::IntID, keyBitCount },
    }*/
    ;


    Table voter1Data, dmv1Data;
    Table voter2Data, dmv2Data;

    voter1Data.init(n, voterSchema);
    dmv1Data.init(n, dvmSchema);

    voter2Data.init(n, voterSchema);
    dmv2Data.init(n, dvmSchema);

    for (auto& c : voter1Data.mColumns) prng.get<i64>(c.mData.data(), c.mData.size());
    for (auto& c : voter2Data.mColumns) prng.get<i64>(c.mData.data(), c.mData.size());
    for (auto& c : dmv1Data.mColumns) prng.get<i64>(c.mData.data(), c.mData.size());
    for (auto& c : dmv2Data.mColumns) prng.get<i64>(c.mData.data(), c.mData.size());
	Timer t;
	//print_all_of_Table(voter1Data);
	std::array<u64, 3> comm_p, cc;
	std::array<u64, 3> comm_0;
	std::array<u64, 3> comm_1;

    auto routine = [&](int i)
    {
        auto& srv = srvs[i];

		srvs[i].mRt.mComm.mNext.resetStats();
		srvs[i].mRt.mComm.mPrev.resetStats();
        SharedTable voter1, voter2, dmv1, dmv2;

        if (i == 0)
        {
            voter1 = srv.localInput(voter1Data);
            voter2 = srv.localInput(voter2Data);
            dmv1 = srv.localInput(dmv1Data);
            dmv2 = srv.localInput(dmv2Data);
        }
        else
        {
            voter1 = srv.remoteInput(0);
            voter2 = srv.remoteInput(0);
            dmv1 = srv.remoteInput(0);
            dmv2 = srv.remoteInput(0);
        }

		if(i==0)
	        t.setTimePoint("start");

		comm_p[i] = (srvs[i].mRt.mComm.mNext.getTotalDataSent() + srvs[i].mRt.mComm.mPrev.getTotalDataSent());

		srvs[i].mRt.mComm.mNext.resetStats();
		srvs[i].mRt.mComm.mPrev.resetStats();
		cc[i] = (srvs[i].mRt.mComm.mNext.getTotalDataSent() + srvs[i].mRt.mComm.mPrev.getTotalDataSent());

        auto select1 = std::vector<SharedTable::ColRef>{ dmv1["NA"], dmv1["SSN"], dmv1["AD"] };
        auto select2 = std::vector<SharedTable::ColRef>{ dmv2["NA"], dmv2["SSN"], dmv2["AD"] };

        auto state1 = srv.leftJoin(dmv1["DL"], voter1["DL"], select1, "registed");
		if (i == 0) t.setTimePoint("left1");
		comm_0[i] = (srvs[i].mRt.mComm.mNext.getTotalDataSent() + srvs[i].mRt.mComm.mPrev.getTotalDataSent());


		srvs[i].mRt.mComm.mNext.resetStats();
		srvs[i].mRt.mComm.mPrev.resetStats();

        auto state2 = srv.leftJoin(dmv2["DL"], voter2["DL"], select2, "registed");
		if (i == 0) t.setTimePoint("left2");
		comm_1[i] = (srvs[i].mRt.mComm.mNext.getTotalDataSent() + srvs[i].mRt.mComm.mPrev.getTotalDataSent());

		srvs[i].mRt.mComm.mNext.resetStats();
		srvs[i].mRt.mComm.mPrev.resetStats();

        SelectQuery select;
        auto SSN = select.joinOn(state1["SSN"], state2["SSN"]);

		if (true)
		{
			print_all_of_SharedTabel(state1,i,srvs);
			print_all_of_SharedTabel(state2,i,srvs);
			auto date1 = select.addInput(state1["AD"]);
			auto date2 = select.addInput(state2["AD"]);
			auto reg1 = select.addInput(state1["registed"]);
			auto reg2 = select.addInput(state2["registed"]);
			select.noReveal("s");

			auto older1 = date1 < date2;
			auto older2 = !older1;
			auto doubleReg = reg1 & reg2;
			auto reveal1 = doubleReg | (older1 & reg1);
			auto reveal2 = doubleReg | (older2 & reg2);

			select.addOutput("NA1", select.addInput(state1["NA"]) * reveal1);
			select.addOutput("NA2", older1);
			


		}
		else
		{
			select.addOutput("SSN", SSN);
			print_all_of_SharedTabel(state2,i,srvs);
		}

        auto intersection = srv.joinImpl(select);
		print_all_of_SharedTabel(intersection, i ,srvs);

		if (i == 0)
		{
			std::cout << "s s " << voter1.rows() << "  " << state2.rows() << "  " << intersection.rows() << std::endl;
			
					
		}
		
		if (i == 0)
			t.setTimePoint("done");

    };




    std::thread t0 = std::thread(routine, 0);
    std::thread t1 = std::thread(routine, 1);
    routine(2);

    t0.join();
    t1.join();

	auto comm0 = (srvs[0].mRt.mComm.mNext.getTotalDataSent() + srvs[0].mRt.mComm.mPrev.getTotalDataSent());
	auto comm1 = (srvs[1].mRt.mComm.mNext.getTotalDataSent() + srvs[1].mRt.mComm.mPrev.getTotalDataSent());
	auto comm2 = (srvs[2].mRt.mComm.mNext.getTotalDataSent() + srvs[2].mRt.mComm.mPrev.getTotalDataSent());
	std::cout << "n = " << n << "   " << comm0 + comm1 + comm2
		<< "\n    cc " << cc[0] + cc[1] + cc[2]
		<< "\n    pp " << comm_p[0] + comm_p[1] + comm_p[2]
		<< "\n    j0 " << comm_0[0] + comm_0[1] + comm_0[2]
		<< "\n    j1 " << comm_1[0] + comm_1[1] + comm_1[2]
		<< "\n    j2 " << comm0 + comm1 + comm2
		<<"\n" << t << std::endl;

}
int main(int argc, char *argv[])
{
	if (argc == 3)
	{
		use_case2(atoi(argv[1]), atoi(argv[2]));
	}
	else
	{
		//DB_threat();
		//DB_test();
		use_case2();
		//eric(10);
	}
}
