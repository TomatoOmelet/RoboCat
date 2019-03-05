class EmojiClient : public Emoji
{
public:
	static	GameObjectPtr	StaticCreate()		{ return GameObjectPtr( new EmojiClient() ); }

	virtual void		Read( InputMemoryBitStream& inInputStream ) override;
	virtual void ChangeTexture(int index) override;
protected:
	EmojiClient();

private:

	SpriteComponentPtr	mSpriteComponent;
};