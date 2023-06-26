#include<iostream>
#include<fstream>
#include<string>

using namespace std;

class User;
class Page;
class SocialMediaApp;
class Post;
class Date;

class Helper
{
public:
	static int StringLength(const char* str)
	{
		int count = 0;
		if (str != 0)
		{
			for (; str[count] != '\0'; count++) {}
		}
		return count;
	}
	static void StringCopy(char*& dest, const char* src) {
		//Deep Copies src into dest.
		int count = StringLength(src);
		char* temp = dest;
		dest = new char[count + 1];
		if (src != 0)
		{
			for (int i = 0; i < count; i++)
			{
				dest[i] = src[i];
			}
			dest[count] = '\0';
		}
		if (temp)
		{
			delete[] temp;
			temp = 0;
		}
	}
	static char* GetStringFromBuffer(const char* str)
	{
		char* string = 0;
		string = new char[StringLength(str) + 1];
		StringCopy(string, str);
		return string;
	}
	static void lower(char* str)
	{
		for (int i = 0; str[i] != '\0'; i++)
		{
			if (str[i] >= 'A' && str[i] <= 'Z')
			{
				str[i] = str[i] + 32;
			}
		}
	}
	static int CompareString(const char* cstring1, const char* cstring2)
	{
		int ascii1 = 0;
		int ascii2 = 0;
		int i = 0;
		while (cstring1[i] != '\0' || cstring2[i] != '\0')
		{
			if (cstring1[i] >= 'A' && cstring1[i] <= 'Z')
				ascii1 = int(cstring1[i] + 32);
			else
				ascii1 = int(cstring1[i]);
			if (cstring2[i] >= 'A' && cstring2[i] <= 'Z')
				ascii2 = int(cstring2[i] + 32);
			else
				ascii2 = int(cstring2[i]);

			if (ascii1 < ascii2 || ascii1 > ascii2)
				return false;
			i++;
		}
		return true;
	}
	static void StringConcatenate(char*& string1, const char* string2)
	{
		int size1 = StringLength(string1);
		int size2 = StringLength(string2);
		char* temp = string1;// Making a temp pointer to point towards the contents of old string1.
		int size3 = size1 + size2 + 1;//1 extra byte for space and 1 for Null character.
		string1 = new char[size3];//Dynamically Allocating CERTAIN space to String 1.
		for (int i = 0; i < size1; i++)
		{
			if (temp[i] != '\0')
			{
				string1[i] = temp[i]; //Storing the old contents of String1 in the new String1.
			}
		}
		int i = size1;
		for (int j = 0; i < size1 + size2 + 1; i++, j++)
		{
			if (string2[j] != '\0')
				string1[i] = string2[j]; //Concatenating String2 in String1.
		}

		string1[i - 1] = '\0';
	}
	static char* GetID(const char* p, int n)
	{
		return 0;
	}
};

class Date
{
private:
	int days;
	int months;
	int years;
public:
	static Date currentDate;
	static void SetCurrentDate(int days, int months, int years)
	{
		currentDate.SetDate(days, months, years);
	}

	Date()
	{
		days = 0;
		months = 0;
		years = 0;
	}
	void ReadDataFromFile(ifstream& input)
	{

		input >> days;
		input >> months;
		input >> years;

	}
	void Print()
	{
		cout << "(" << days << "/" << months << "/" << years << ")";
	}
	void SetDate(int _days, int _months, int _years)
	{
		days = _days;
		months = _months;
		years = _years;

	}
	bool CompareDate(Date& postDate)
	{
		if (postDate.years == years)
		{
			if (postDate.months < months)
			{
				if ((postDate.days == 28 && days == 1) || (postDate.days == 31 && days == 1) || (postDate.days == 30 && days == 1))
				{
					return true;
				}
			}
			else if (months == postDate.months)
			{
				if (postDate.days == days - 1 || postDate.days == days)
				{
					return true;
				}
			}
		}
		return false;
	}
	int YearDifference(Date& date)
	{
		return date.years - years;
	}
	bool CheckIfRecent(Date rhs)
	{
		if (rhs.years == years)
		{
			if (rhs.months > months)
			{
				return true;
			}
			else if (rhs.months == months)
			{
				if (rhs.days > days)
				{
					return true;
				}
			}
		}
		else if (rhs.years > years)
			return true;
		return false;
	}
};

Date Date::currentDate;

class Object
{
protected:
	char* id = 0;
public:
	virtual void addPost(Post*& pst) = 0;
	virtual char* GetName() = 0;
	virtual void Print() = 0;
	virtual bool SearchPost(Post*) = 0;
	virtual void SeeYourMemories() = 0;
	virtual void viewTimeline() = 0;
	virtual void ViewFriendsList() {}
	virtual void ViewPagesList() {}
	virtual void ViewHome() {}
	virtual void ShareMemory(Post*&, const char*) {}
	virtual void SortPosts() = 0;
	virtual void PostComment(Post*&, const char*) {}



};

class Comment
{
private:
	Object* Commenter;
	char* id;
	char* contents;
public:
	void SetValues(const char* _id, const char* _contents, Object* _commenter)
	{
		id = Helper::GetStringFromBuffer(_id);
		contents = Helper::GetStringFromBuffer(_contents);
		Commenter = _commenter;
	}
	void Print()
	{
		cout << Commenter->GetName() << " Wrote:" << "\"" << contents << "\"";
	}
	~Comment()
	{

		if (id)
			delete[] id;
		if (Commenter)
			Commenter = 0;
		if (contents)
			delete[] contents;
	}
};

class Activity
{
private:
	int type;
	char* value;
public:
	Activity()
	{
		type = 0;
		value = 0;
	}
	void ReadDataFromFile(ifstream& input)
	{
		char buffer[100];
		input >> type;
		input.getline(buffer, 100);

		value = Helper::GetStringFromBuffer(buffer);
	}
	void Print()
	{
		if (type == 1)
			cout << " is feeling ";
		else if (type == 2)
			cout << "is thinking About ";
		else if (type == 3)
			cout << "is making ";
		else
			cout << "is celebrating ";

		cout << value << endl;
	}
	~Activity()
	{
		if (value)
			delete[] value;
	}


};

class Post
{
protected:
	char* id = 0;
	Activity* status = 0;
	Object* poster = 0;
	Comment** comments = 0;
	Object** likerList = 0;
	int likeCount = 0;
	int commentCount = 0;
	char* caption = 0;
	Date postDate;

public:
	Post()
	{
		id = 0;
		caption = 0;
		poster = 0;
		comments = 0;
		likerList = 0;
	}
	Post(const char* _caption, Date _postDate) : postDate(_postDate)
	{
		if (_caption)
		{
			int size = Helper::StringLength(_caption) + 1;
			caption = new char[size];
			Helper::StringCopy(caption, _caption);
		}
	}
	void ReadDataFromFile(ifstream& input)
	{
		int activityStatus = 0;
		char buffer[1000];

		input >> activityStatus;

		input >> buffer;
		id = Helper::GetStringFromBuffer(buffer);

		postDate.ReadDataFromFile(input);

		input.ignore();
		input.getline(buffer, 100);
		caption = Helper::GetStringFromBuffer(buffer);

		if (activityStatus == 2)
		{
			status = new Activity;
			status->ReadDataFromFile(input);
		}
	}
	void addComment(Comment*& _comment)
	{
		if (commentCount <= 10)
		{
			commentCount++;
			Comment** temp = comments;
			comments = new Comment * [commentCount];
			if (temp)
			{
				for (int i = 0; i < commentCount - 1; i++)
				{
					comments[i] = temp[i];
				}
			}
			comments[commentCount - 1] = _comment;
		}
		else
			cout << "Maximum Comment Count for this Post has been Reached. Cannot add any more Comments.\n\n";

	}
	void addLiker(Object*& liker)
	{
		if (likeCount <= 10)
		{
			likeCount++;
			Object** temp = likerList;
			likerList = new Object * [likeCount];
			if (temp)
			{
				int i = 0;
				for (; i < likeCount - 1; i++)
				{
					likerList[i] = temp[i];
				}
				delete temp;
			}
			likerList[likeCount - 1] = liker;
		}
		else
		{
			cout << "Maximum like count reached. Cannot add any more Likers.\n";
		}
	}
	virtual void Print(const bool showDate = true, const bool showComments = true)
	{
		cout << "--- " << poster->GetName() << " ";
		if (status)
			status->Print();
		cout << "\"" << caption << "\"" << "---";
		if (showDate)
			postDate.Print();
		cout << endl;
		if (showComments)
			for (int i = 0; i < commentCount; i++)
			{
				cout << endl << "\t\t";
				comments[i]->Print();
			}
	}
	char* GetPostID()
	{
		return id;

	}
	Date GetPostDate()
	{
		return postDate;

	}
	void setPoster(Object*& Poster)
	{
		poster = Poster;
	}
	void PrintLikersList()
	{
		for (int i = 0; i < likeCount; i++)
		{
			likerList[i]->Print();
			cout << endl;
		}
	}
	Object* GetPoster()
	{
		return poster;

	}
	~Post()
	{
		if (id)
			delete[] id;
		if (poster)
			poster = 0;
		if (status)
			delete status;
		for (int i = 0; i < commentCount; i++)
		{
			delete comments[i];
		}
		if (likerList)
			delete[] likerList;
	}
};

class Memory : public Post
{
private:
	Post* originalPost;
public:
	Memory(const char* text, Date& date, Post*& post, int count) : originalPost(post), Post(text, date)
	{
		id = Helper::GetID("P", count);

		poster = post->GetPoster();

	}
	void Print(const bool showDate = true, const bool showComments = true)
	{

		cout << "~~~ " << (originalPost->GetPoster())->GetName() << " Shared a Memory~~~";
		if (showDate)
			postDate.Print();
		cout << endl;
		cout << "\"" << caption << "\"" << endl;
		int timeDiff = (originalPost->GetPostDate()).YearDifference(Date::currentDate);
		if (timeDiff == 1)
			cout << "(" << timeDiff << " Year Ago )\n";
		else
			cout << "(" << timeDiff << " Years Ago )\n";
		originalPost->Print(true, false);
	}
	~Memory()
	{
		if (originalPost)
			delete originalPost;
	}
};

class Page : public Object
{
private:
	char* pageTitle = 0;
	static int pageCount;
	Post** posts = 0;
	int postsCount = 0;
public:
	void ReadDataFromFile(ifstream& input)
	{
		char temp[50];

		input >> temp;
		id = Helper::GetStringFromBuffer(temp);

		input.ignore();

		input.getline(temp, 50);
		pageTitle = Helper::GetStringFromBuffer(temp);

		pageCount++;
	}
	char* GetPageID()
	{
		return id;

	}
	void Print()
	{
		cout << id << "-" << pageTitle;
	}
	void addPost(Post*& post)
	{
		postsCount++;
		Post** temp = posts;
		posts = new Post * [postsCount];
		if (temp)
		{
			for (int i = 0; i < postsCount - 1; i++)
			{
				posts[i] = temp[i];
			}
		}
		posts[postsCount - 1] = post;
	}
	char* GetName()
	{
		return pageTitle;
	}
	int GetPostsCount()
	{
		return postsCount;

	}
	void viewTimeline()
	{
		if (postsCount == 0)
		{
			cout << pageTitle << " has no posts.\n";
		}
		else
		{

			cout << pageTitle << " - TimeLine\n\n";

			for (int i = 0; i < postsCount; i++)
			{
				posts[i]->Print();
				cout << endl << endl;
			}
		}
	}
	void ShowRecentPosts()
	{
		int totalPosts = postsCount;
		Date postDate;
		for (int i = 0; i < postsCount; i++)
		{
			postDate = posts[i]->GetPostDate();
			bool ShowPost = Date::currentDate.CompareDate(postDate);
			if (ShowPost)
			{
				posts[i]->Print(false);
				cout << endl << endl;
			}
		}
	}
	bool SearchPost(Post* post)
	{
		if (postsCount)
		{
			for (int i = 0; i < postsCount; i++)
			{
				if (posts[i] == post)
					return true;
			}
		}
		return false;
	}
	void SeeYourMemories()
	{
		cout << "\nWe hope you enjoy looking back and sharing your memories on Facebook, from the most recent to those long ago\n\n";
		int count = 0;
		for (int i = 0; i < postsCount; i++)
		{
			int timeDiff = (posts[i]->GetPostDate()).YearDifference(Date::currentDate);
			if (timeDiff > 0)
			{
				cout << "On This Day\n";
				if (timeDiff == 1)
					cout << timeDiff << " Year Ago\n\n";
				else
					cout << timeDiff << " Years Ago\n\n";
				posts[i]->Print();
				count++;
			}
		}
		if (!count)
			cout << "The User has No Memories :(\n";
	}
	void SortPosts()
	{
		for (int i = 0; i < postsCount; i++)
		{
			for (int j = i; j < postsCount - i; j++)
			{
				bool Recent = (posts[i]->GetPostDate()).CheckIfRecent(posts[j]->GetPostDate());
				if (Recent)
				{
					Post* temp = posts[i];
					posts[i] = posts[j];
					posts[j] = posts[i];
				}
			}
		}
	}
	~Page()
	{
		if (this)
		{
			if (pageTitle)
			{
				delete[] pageTitle;
			}
			if (posts)
				for (int i = 0; i < postsCount; i++)
				{
					delete posts[i];
				}

		}
		
	}
};
int Page::pageCount = 0;

class User : public Object
{
private:
	char* fname;
	char* lname;
	User** friendsList = 0;
	Page** likedPages = 0;
	Post** posts = 0;
	int likedPagesCount = 0;
	int postsCount = 0;
	int totalFriends = 0;

public:
	User(const char* _userID = 0, const char* _fName = 0, const char* _lName = 0)
	{
		id = Helper::GetStringFromBuffer(_userID);
		fname = Helper::GetStringFromBuffer(_fName);
		lname = Helper::GetStringFromBuffer(_lName);
		likedPagesCount = 0;
	}
	void ReadDataFromFile(ifstream& input)
	{
		char temp[50];

		input >> temp;
		id = Helper::GetStringFromBuffer(temp);

		input >> temp;
		fname = Helper::GetStringFromBuffer(temp);

		input >> temp;
		lname = Helper::GetStringFromBuffer(temp);

	}
	void LikedPage(Page* pagePtr)
	{
		if (likedPagesCount <= 10)
		{
			int oldSize = likedPagesCount;
			Page** temp = likedPages;
			likedPagesCount++;
			likedPages = new Page * [likedPagesCount];
			int i = 0;
			if (temp)
				for (; i < oldSize; i++)
				{
					likedPages[i] = new Page;
					likedPages[i] = temp[i];
				}
			likedPages[i] = pagePtr;
			if (temp)
				delete temp;
		}
		else
		{
			cout << "Maximum Like Count for Pages Reached. Cannot add any more Likers.\n\n";
		}
	}
	void AddFriend(User**& userPtr)
	{
		if (totalFriends <= 10)
		{
			friendsList = new User * [totalFriends];
			for (int i = 0; i < totalFriends; i++)
			{
				friendsList[i] = userPtr[i];
			}
		}
		else
			cout << "Maximum Friend Count for this User Reached. Cannot add any more Friends.\n\n";

	}
	void SetTotalFriends(int friends)
	{
		totalFriends = friends;
	}
	int GetTotalFriends()
	{
		return totalFriends;
	}
	char* GetUserID()
	{
		return id;
	}
	void ViewFriendsList()
	{
		cout << fname << " " << lname << "-Friends List:-";
		cout << endl << endl;
		if (totalFriends)
			for (int i = 0; i < totalFriends; i++)
			{
				friendsList[i]->Print();
				cout << endl;
			}
		else
			cout << "The User has No Friends.\n";
	}
	void ViewPagesList()
	{
		cout << fname << " " << lname << "-Liked Pages:-";
		cout << endl << endl;
		if (likedPagesCount)
			for (int i = 0; i < likedPagesCount; i++)
			{
				likedPages[i]->Print();
				cout << endl;
			}
		else
			cout << "The User has No Liked Pages.\n";
	}
	void Print()
	{
		cout << id << "-" << fname << " " << lname;
	}
	void viewTimeline()
	{
		if (postsCount == 0)
		{
			cout << fname << " " << lname << " has no posts.\n";
		}
		else
		{

			cout << fname << " " << lname << " - TimeLine\n\n";

			for (int i = 0; i < postsCount; i++)
			{
				posts[i]->Print();
				cout << endl << endl;
			}
		}
	}
	void addPost(Post*& pst)
	{
		postsCount++;
		Post** temp = posts;
		posts = new Post * [postsCount];
		if (temp)
		{
			for (int i = 0; i < postsCount - 1; i++)
			{
				posts[i] = temp[i];
			}
		}
		posts[postsCount - 1] = pst;
	}
	char* GetName()
	{
		char* buffer = new char[100];
		Helper::StringCopy(buffer, fname);
		buffer[Helper::StringLength(fname)] = ' ';
		buffer[(Helper::StringLength(fname)) + 1] = '\0';
		Helper::StringConcatenate(buffer, lname);
		return buffer;
	}
	void SeeYourMemories()
	{
		cout << "\nWe hope you enjoy looking back and sharing your memories on Facebook, from the most recent to those long ago\n\n";

		int count = 0;
		for (int i = 0; i < postsCount; i++)
		{
			int timeDiff = (posts[i]->GetPostDate()).YearDifference(Date::currentDate);
			if (timeDiff > 0)
			{
				cout << "On This Day\n";
				if (timeDiff == 1)
					cout << timeDiff << " Year Ago\n\n";
				else
					cout << timeDiff << " Years Ago\n\n";
				posts[i]->Print();
				cout << endl << endl;
				count++;
			}
		}
		if (!count)
			cout << "The User has No Memories :(\n";
	}
	void ViewHome()
	{
		for (int i = 0; i < totalFriends; i++)
		{
			friendsList[i]->ShowRecentPosts();

		}
		for (int i = 0; i < likedPagesCount; i++)
		{
			likedPages[i]->ShowRecentPosts();
		}
	}
	void ShowRecentPosts()
	{
		int totalPosts = postsCount;
		Date postDate;
		for (int i = 0; i < totalPosts; i++)
		{
			postDate = posts[i]->GetPostDate();
			bool showPost = Date::currentDate.CompareDate(postDate);
			if (showPost)
			{
				posts[i]->Print(false);
				cout << endl << endl;
			}
		}
	}
	bool SearchPost(Post* post)
	{
		if (postsCount)
		{
			for (int i = 0; i < postsCount; i++)
			{
				if (posts[i] == post)
					return true;
			}
		}
		return false;
	}
	void SortPosts()
	{
		for (int i = 0; i < postsCount; i++)
		{
			for (int j = i; j < postsCount; j++)
			{
				bool Recent = (posts[i]->GetPostDate()).CheckIfRecent(posts[j]->GetPostDate());
				if (Recent)
				{
					Post* temp = posts[i];
					posts[i] = posts[j];
					posts[j] = temp;
				}
			}
		}
	}
	void ShareMemory(Post*& post, const char* _caption)
	{
		bool found = SearchPost(post);
		if (found)
		{
			Post* newMemory = new Memory(_caption, Date::currentDate, post, postsCount);
			addPost(newMemory);
		}
		else
		{
			cout << "Can't Make a Memory out of Nothing :D \n";
		}
	}
	void PostComment(Post*& postPtr, const char* text)
	{
		Comment* comment = new Comment;
		comment->SetValues("u", text, this);
		postPtr->addComment(comment);
	}
	~User()
	{
		if (fname)
			delete[] fname;
		if (lname)
			delete[] lname;
		if (friendsList)
			delete[] friendsList;
		if (likedPages)
			delete[] likedPages;
		for (int i = 0; i < postsCount; i++)
		{
			delete posts[i];
		}
	}

};

class SocialMediaApp
{
private:
	Page** pages;
	User** users;
	Post** posts;
	Comment** comments;
	int totalUsers;
	int totalPages;
	int totalPost;
	int totalComments;

public:

	void Load()
	{
		LoadPagesFromFile("PageData.txt");
		LoadUsersFromFile("UserData.txt");
		LoadPostsFromFile("PostData.txt");
		LoadCommentsFromFile("CommentData.txt");
	}

	void LoadPagesFromFile(const char* filename)

	{
		ifstream input(filename);
		input >> totalPages;
		pages = new Page * [totalPages];
		for (int i = 0; i < totalPages; i++)
		{
			pages[i] = new Page;
			pages[i]->ReadDataFromFile(input);
		}
		input.close();
	}
	void LoadUsersFromFile(const char* filename)

	{
		ifstream input(filename);
		input >> totalUsers;
		users = new User * [totalUsers];
		char buffer[50] = "";
		char*** tempFriendsList = 0;
		tempFriendsList = new char** [totalUsers];
		for (int i = 0; i < totalUsers; i++)
		{
			users[i] = new User;
			users[i]->ReadDataFromFile(input);
			tempFriendsList[i] = new char* [10];
			int k = 0;
			input >> buffer;
			int totalFriends = 0;
			while (atoi(buffer) != -1)
			{
				totalFriends++;
				tempFriendsList[i][k] = Helper::GetStringFromBuffer(buffer);
				input >> buffer;
				k++;
			}
			users[i]->SetTotalFriends(totalFriends);
			input >> buffer;
			while (atoi(buffer) != -1)
			{
				Page* pgPtr = SearchPageByID(buffer);
				users[i]->LikedPage(pgPtr);
				input >> buffer;
			}
		}
		input.close();
		for (int i = 0; i < totalUsers; i++)
		{
			User** Ptr = new User * [users[i]->GetTotalFriends()];
			int friends = users[i]->GetTotalFriends();
			for (int j = 0; j < friends; j++)
			{
				Ptr[j] = SearchUserByID(tempFriendsList[i][j]);
			}
			users[i]->AddFriend(Ptr);
		}

		for (int i = 0; i < totalUsers; i++)
		{
			int friends = users[i]->GetTotalFriends();
			for (int j = 0; j < friends; j++)
			{
				if (tempFriendsList[i][j])
				{
					delete[] tempFriendsList[i][j];
					tempFriendsList[i][j] = 0;
				}
			}
		}
		if (tempFriendsList)
		{
			delete[] tempFriendsList;
			tempFriendsList = 0;
		}
	}
	void LoadPostsFromFile(const char* filename)
	{
		ifstream input(filename);
		input >> totalPost;
		posts = new Post * [totalPost];
		char buffer[100] = "";
		Object* Poster;
		Object* Liker;
		for (int i = 0; i < totalPost; i++)
		{
			posts[i] = new Post;
			posts[i]->ReadDataFromFile(input);
			input >> buffer;
			Poster = SearchObjectByID(buffer);
			input >> buffer;
			while (atoi(buffer) != -1)
			{
				Liker = SearchObjectByID(buffer);

				posts[i]->addLiker(Liker);
				input >> buffer;
			}
			Poster->addPost(posts[i]);
			posts[i]->setPoster(Poster);
		}
	}
	void LoadCommentsFromFile(const char* filename)
	{
		ifstream input(filename);
		input >> totalComments;


		comments = new Comment * [totalComments];
		char id[100];
		char commentedOn[100];
		char commentedBy[100];
		char contents[150];

		for (int i = 0; i < totalComments; i++)
		{
			comments[i] = new Comment;

			input >> id;
			input >> commentedOn;
			input >> commentedBy;
			input.getline(contents, 100);


			Post* postPtr = SearchPostByID(commentedOn);
			Object* objPtr = SearchObjectByID(commentedBy);
			comments[i]->SetValues(id, contents, objPtr);

			postPtr->addComment(comments[i]);
		}
	}


	Page* SearchPageByID(const char* str)
	{
		for (int i = 0; i < totalPages; i++)
		{
			if (Helper::CompareString(pages[i]->GetPageID(), str))
			{
				return pages[i];
			}
		}
		return NULL;
	}
	User* SearchUserByID(const char* str)
	{
		for (int i = 0; i < totalUsers; i++)
		{
			if (Helper::CompareString(users[i]->GetUserID(), str))
			{
				return users[i];
			}
		}
		return NULL;
	}
	Post* SearchPostByID(const char* str)
	{
		for (int i = 0; i < totalPost; i++)
		{
			if (Helper::CompareString(posts[i]->GetPostID(), str))
			{
				return posts[i];
			}
		}
		return NULL;
	}
	Object* SearchObjectByID(const char* str)
	{
		Object* ob = 0;
		if (str[0] == 'u')
			ob = SearchUserByID(str);
		else
			ob = SearchPageByID(str);
		return ob;
	}


	void LikePost(const char* pID, Object*& obj)

	{
		Post* post = SearchPostByID(pID);
		post->addLiker(obj);
	}
	void ViewLikedList(const char* pID)

	{
		cout << "Post Liked By:\n\n";
		Post* post = SearchPostByID(pID);
		post->PrintLikersList();
	}
	void ViewPost(const char* pID)
	{
		Post* post = SearchPostByID(pID);
		post->Print();
	}
	void ViewPage(const char* pID)
	{
		Page* page = SearchPageByID(pID);
		page->viewTimeline();
	}
	void Execute()
	{
		cout << "+-------------------------------------------------------------------------------------------------------------+\n";
		cout << "|\t\t\t\t\tCommand: SetDate\t\t\t\t\t              |\n";
		cout << "+-------------------------------------------------------------------------------------------------------------+\n";
		cout << endl;
		Date::SetCurrentDate(15, 11, 2017);
		Date::currentDate.Print(); cout << " has been set as System Date successfully.\n\n";

		cout << "+-------------------------------------------------------------------------------------------------------------+\n";
		cout << "|\t\t\t\t\tCommand: SetUser\t\t\t\t\t              |\n";
		cout << "+-------------------------------------------------------------------------------------------------------------+\n";
		cout << endl;
		Object* currUser = 0;
		currUser = SearchObjectByID("u3");
		if (currUser)
			cout << currUser->GetName() << " has been set succesfully\n\n";
		else
		{
			cout << "Error: Invalid User ID.\nProgram Exiting\n\n";
			return;
		}


		cout << "+-------------------------------------------------------------------------------------------------------------+\n";
		cout << "|\t\t\t\t\tCommand: ViewFriendsList\t\t\t\t\t      |\n";
		cout << "+-------------------------------------------------------------------------------------------------------------+\n";
		cout << endl;
		currUser->ViewFriendsList();

		cout << "\n+-------------------------------------------------------------------------------------------------------------+\n";
		cout << "|\t\t\t\t\tCommand: ViewLikedPages\t\t\t\t\t\t      |\n";
		cout << "+-------------------------------------------------------------------------------------------------------------+\n";
		cout << endl;
		currUser->ViewPagesList();

		cout << "\n+-------------------------------------------------------------------------------------------------------------+\n";
		cout << "|\t\t\t\t\tCommand: ViewHome\t\t\t\t\t\t      |\n";
		cout << "+-------------------------------------------------------------------------------------------------------------+\n";
		cout << endl;
		currUser->ViewHome();


		cout << "\n+-------------------------------------------------------------------------------------------------------------+\n";
		cout << "|\t\t\t\t\tCommand: ViewTimeLine\t\t\t\t\t\t      |\n";
		cout << "+-------------------------------------------------------------------------------------------------------------+\n";
		cout << endl;
		currUser->SortPosts();
		currUser->viewTimeline();

		cout << "\n+-------------------------------------------------------------------------------------------------------------+\n";
		cout << "|\t\t\t\t\tCommand: ViewLikedList\t\t\t\t\t\t      |\n";
		cout << "+-------------------------------------------------------------------------------------------------------------+\n";
		cout << endl;
		ViewLikedList("post5");


		cout << "\n+-------------------------------------------------------------------------------------------------------------+\n";
		cout << "|\t\t\t\t\tCommand: LikePost\t\t\t\t\t\t      |\n";
		cout << "+-------------------------------------------------------------------------------------------------------------+\n";
		cout << endl;
		LikePost("post5", currUser);
		ViewLikedList("post5");


		cout << "\n+-------------------------------------------------------------------------------------------------------------+\n";
		cout << "|\t\t\t\t\tCommand: PostComment\t\t\t\t\t\t      |\n";
		cout << "+-------------------------------------------------------------------------------------------------------------+\n";
		cout << endl;
		Post* temp = SearchPostByID("post4");
		currUser->PostComment(temp, "Good Luck For Your Result");
		ViewPost("post4");
		cout << endl;
		cout << endl;

		ViewPost("post7");
		cout << endl << endl;
		temp = SearchPostByID("post7");
		currUser->PostComment(temp, "yahi yahi");
		ViewPost("post7");

		cout << "\n+-------------------------------------------------------------------------------------------------------------+\n";
		cout << "|\t\t\t\t\tCommand: SeeYourMemories()\t\t\t\t\t\t      |\n";
		cout << "+-------------------------------------------------------------------------------------------------------------+\n";
		currUser->SeeYourMemories();
		cout << endl;

		cout << "\n+-------------------------------------------------------------------------------------------------------------+\n";
		cout << "|\t\t\t\t\tCommand: ShareMemory\t\t\t\t\t\t      |\n";
		cout << "+-------------------------------------------------------------------------------------------------------------+\n";
		cout << endl;
		temp = SearchPostByID("post10");
		currUser->ShareMemory(temp, "Never knew I would be successful in this field");
		currUser->SortPosts();
		currUser->viewTimeline();

		cout << "\n+-------------------------------------------------------------------------------------------------------------+\n";
		cout << "|\t\t\t\t\tCommand: ViewPage\t\t\t\t\t\t      |\n";
		cout << "+-------------------------------------------------------------------------------------------------------------+\n";
		cout << endl;
		ViewPage("p1");

		cout << "+-------------------------------------------------------------------------------------------------------------+\n";
		cout << "|\t\t\t\t\tCommand: SetUser\t\t\t\t\t              |\n";
		cout << "+-------------------------------------------------------------------------------------------------------------+\n";
		cout << endl;


		currUser = SearchObjectByID("u11");
		if (currUser)
			cout << currUser->GetName() << " has been set succesfully\n\n";
		else
		{
			cout << "Error: Invalid User ID.\nProgram Exiting\n\n";
			return;
		}


		cout << "\n+-------------------------------------------------------------------------------------------------------------+\n";
		cout << "|\t\t\t\t\tCommand: ViewHome\t\t\t\t\t\t      |\n";
		cout << "+-------------------------------------------------------------------------------------------------------------+\n";
		cout << endl;
		currUser->ViewHome();



		cout << "\n+-------------------------------------------------------------------------------------------------------------+\n";
		cout << "|\t\t\t\t\tCommand: ViewTimeLine\t\t\t\t\t\t      |\n";
		cout << "+-------------------------------------------------------------------------------------------------------------+\n";
		cout << endl;
		currUser->viewTimeline();


		cout << "\n+-------------------------------------------------------------------------------------------------------------+\n";
		cout << "|\t\t\t\t\t The END\t\t\t\t\t\t\t      |\n";
		cout << "+-------------------------------------------------------------------------------------------------------------+\n";
		cout << endl;

		cout << endl << endl;
	}

	~SocialMediaApp()
	{


		if (posts)
		{
			delete[] posts;
		}

		if (users)
		{
			for (int i = 0; i < totalUsers; i++)
			{
				if (users[i])
					delete users[i];
			}
			delete[] users;

		}


		if (pages)
		{
			for (int i = 0; i < totalPages; i++)
			{
				if (pages[i])
					delete pages[i];
			}
			delete[] pages;
		}
		if (comments)
		{
			delete[] comments;
		}

	}


};


int main()
{


	SocialMediaApp fb;
	fb.Load();
	fb.Execute();
	return 0;
}