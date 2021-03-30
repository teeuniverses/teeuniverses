/*
 * Copyright (C) 2016 necropotame (necropotame@gmail.com)
 * 
 * This file is part of TeeUniverse.
 * 
 * TeeUniverse is free software: you can redistribute it and/or  modify
 * it under the terms of the GNU Affero General Public License, version 3,
 * as published by the Free Software Foundation.
 *
 * TeeUniverse is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with TeeUniverse.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __CLIENT_ASSETSEDITOR_VIEWMAP__
#define __CLIENT_ASSETSEDITOR_VIEWMAP__

#include <client/gui/listlayout.h>
#include <editor/gui/view.h>

class CViewMap : public CViewManager::CView
{
public:
	class ScopedGroupSetter
	{
	public:
		explicit ScopedGroupSetter(CViewMap *pViewMap);
		~ScopedGroupSetter();

	private:
		CViewMap *m_ViewMap;
	};
	
	class CCursorTool : public CViewManager::CView::CCursorTool
	{
	protected:
		CViewMap* m_pViewMap;

	public:
		CCursorTool(CViewMap* pViewMap, const CLocalizableString& LString, CAssetPath IconPath) :
			CViewManager::CView::CCursorTool(pViewMap, LString, IconPath),
			m_pViewMap(pViewMap)
		{
			
		}
		
		inline CViewMap* ViewMap() { return m_pViewMap; }
	};

protected:
	bool m_GridAligned;
	bool m_CameraDraged;
	float m_ZoneOpacity;
	bool m_ShowGrid;
	bool m_ShowMeshes;
	int m_ShowEntities;
	bool m_ZoomLockedToUnit;
	int m_LoD;
	
	std::unique_ptr<class CMapRenderer> m_pMapRenderer;
	
	CView::CCursorTool* m_pCursorTool_MapStamp;
	CView::CCursorTool* m_pCursorTool_MapFill;
	CView::CCursorTool* m_pCursorTool_MapTransform;
	CView::CCursorTool* m_pCursorTool_MapEdit;
	CView::CCursorTool* m_pCursorTool_MapEraser;
	CView::CCursorTool* m_pCursorTool_MapCrop;
	CView::CCursorTool* m_pCursorTool_MapAddVertex;
	CView::CCursorTool* m_pCursorTool_MapWeightVertex;
	
	std::vector< std::pair<CAssetPath, std::vector<int> > > m_ZoneDataMemory;

public:
	CViewMap(CGuiEditor* pAssetsEditor);
	virtual void Update(bool ParentEnabled);
	virtual void RenderView();
	virtual void OnMouseMove();
	virtual void OnButtonClick(int Button);
	virtual void OnButtonRelease(int Button);
	
	inline class CMapRenderer* MapRenderer() { return m_pMapRenderer.get(); }
	
	CAssetPath GetMapPath();
	CAssetPath GetMapGroupPath();
	
	inline float GetZoneOpacity() const { return m_ZoneOpacity; }
	inline void SetZoneOpacity(float Value) { m_ZoneOpacity = Value; }
	
	inline int GetShowEntites() const { return m_ShowEntities; }
	inline void SetShowEntites(int Value) { m_ShowEntities = Value; }
	
	inline int GetGridAlign() const { return m_GridAligned; }
	inline void SetGridAlign(int Value) { m_GridAligned = Value; }
	
	inline int GetLoD() const { return m_LoD; }
	inline void SetLoD(int Value) { m_LoD = Value; }
	
	float GetCameraZoom();
	void SetCameraZoom(float Value);
	void SetCameraZoomToUnit();
	
	void MemorizeZoneData(const CAssetPath& AssetPath, const std::vector<int>& DataInt);
	const std::vector<int>* GetMemorizedZoneData(const CAssetPath& AssetPath);
};

#endif
