/*!
	@file
	@author		Albert Semenov
	@date		08/2010
*/
#include "precompiled.h"
#include "SeparatorListControl.h"
#include "SkinManager.h"

namespace tools
{

	SeparatorListControl::SeparatorListControl(MyGUI::Widget* _parent) :
		wraps::BaseLayout("SeparatorListControl.layout", _parent),
		mList(nullptr),
		mCurrentSkin(nullptr)
	{
		assignWidget(mList, "List");

		mList->eventListChangePosition += MyGUI::newDelegate(this, &SeparatorListControl::notifyChangePosition);

		SkinManager::getInstance().eventChangeSelection += MyGUI::newDelegate(this, &SeparatorListControl::notifyChangeSelection);
		advice();
	}

	SeparatorListControl::~SeparatorListControl()
	{
		SkinManager::getInstance().eventChangeSelection -= MyGUI::newDelegate(this, &SeparatorListControl::notifyChangeSelection);
		unadvice();

		mList->eventListChangePosition -= MyGUI::newDelegate(this, &SeparatorListControl::notifyChangePosition);
	}

	void SeparatorListControl::notifyChangePosition(MyGUI::List* _sender, size_t _index)
	{
		if (mCurrentSkin != nullptr)
		{
			SeparatorItem* item = nullptr;

			if (_index != MyGUI::ITEM_NONE)
				item = *mList->getItemDataAt<SeparatorItem*>(_index);

			mCurrentSkin->getSeparators().setItemSelected(item);
		}
	}

	void SeparatorListControl::notifyChangeSelection()
	{
		unadvice();
		advice();
	}

	void SeparatorListControl::unadvice()
	{
		if (mCurrentSkin != nullptr)
		{
			ItemHolder<SeparatorItem>::EnumeratorItem separators = mCurrentSkin->getSeparators().getChildsEnumerator();
			while (separators.next())
			{
				SeparatorItem* item = separators.current();
				item->getPropertySet()->eventChangeProperty -= MyGUI::newDelegate(this, &SeparatorListControl::notifyChangeProperty);
			}

			mCurrentSkin = nullptr;
			updateList();
		}
	}

	void SeparatorListControl::advice()
	{
		mCurrentSkin = SkinManager::getInstance().getItemSelected();

		if (mCurrentSkin != nullptr)
		{
			ItemHolder<SeparatorItem>::EnumeratorItem separators = mCurrentSkin->getSeparators().getChildsEnumerator();
			while (separators.next())
			{
				SeparatorItem* item = separators.current();
				item->getPropertySet()->eventChangeProperty += MyGUI::newDelegate(this, &SeparatorListControl::notifyChangeProperty);
			}

			updateList();
		}
	}

	void SeparatorListControl::notifyChangeProperty(Property* _sender, const MyGUI::UString& _value)
	{
		updateList();
	}

	void SeparatorListControl::updateList()
	{
		mList->setIndexSelected(MyGUI::ITEM_NONE);
		mList->removeAllItems();

		if (mCurrentSkin != nullptr)
		{
			SeparatorItem* selectedItem = mCurrentSkin->getSeparators().getItemSelected();

			ItemHolder<SeparatorItem>::EnumeratorItem separators = mCurrentSkin->getSeparators().getChildsEnumerator();
			while (separators.next())
			{
				size_t index = mList->getItemCount();

				SeparatorItem* item = separators.current();

				Property* prop = item->getPropertySet()->getChild("Visible");
				if (prop != nullptr && !isValueTrue(prop->getValue()))
					mList->addItem("#808080" + item->getName(), item);
				else
					mList->addItem(item->getName(), item);

				if (item == selectedItem)
					mList->setIndexSelected(index);
			}
		}
	}

	bool SeparatorListControl::isValueTrue(const MyGUI::UString& _value)
	{
		return (_value == "True");
	}

} // namespace tools
