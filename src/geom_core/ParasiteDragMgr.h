//
// This file is released under the terms of the NASA Open Source Agreement (NOSA)
// version 1.3 as detailed in the LICENSE file which accompanies this software.
//

// ParasiteDragMgr.h: interface for the ParasiteDrag Singleton.
//
//////////////////////////////////////////////////////////////////////

#if !defined(PARASITEDRAG__INCLUDED_)
#define PARASITEDRAG__INCLUDED_

#include "Geom.h"
#include "Parm.h"
#include "Util.h"

#include <string>
#include <vector>


// Structure containing all main table data
struct ParasiteDragTableRow
{
    string GeomID;
    string SubSurfID;
    string Label;
    double Swet;
    double Lref;
    double Re;
    double Roughness;
    double TeTwRatio;
    double TawTwRatio;
    double PercLam;
    double Cf;
    double fineRat;
    int GeomShapeType;
    int FFEqnChoice;
    string FFEqnName;
    double FF;
    double Q;
    double f;
    double CD;
    double PercTotalCd;
    int GroupedAncestorGen;
    int SurfNum;
    bool ExpandedList;
};

// Structure containing all excres table data
struct ExcrescenceTableRow
{
    string Label;
    int Type;
    string TypeString;
    double Input;
    double Amount;
    double PercTotalCd;
    double f;
};

//==== ParasiteDrag Manager ====//
class ParasiteDragMgrSingleton : public ParmContainer
{
public:
    // Required Refresh function for NEW file
    virtual void Renew();

    // Default Struct Method
    void SetDefaultStruct();

    // Required for Mgr Style Codes
    static ParasiteDragMgrSingleton& getInstance()
    {
        static ParasiteDragMgrSingleton instance;
        return instance;
    }
    virtual void ParmChanged(Parm* parm_ptr, int type); // Required for extensions of ParmContainers

    // Main Table Related Functions
    void InitTableVec(); // Initialize all table rows to default struct
    void LoadMainTableUserInputs(); // Load User Input Parm Values from Geoms

    // Calculation Methods
    void SetupFullCalculation();
    int CalcRowSize();
    void Calculate_Swet();
    void Calculate_Lref();
    void CalcReferenceBodyLength(int index);
    void CalcReferenceChord(int index);
    void Calculate_fineRat();

    // Setter Methods
    void SetSref(double sref) { m_Sref.Set(sref); }
    void SetActiveGeomVec();

    // Getter Methods
    vector < ParasiteDragTableRow > GetMainTableVec() { return m_TableRowVec; }
    vector <string> GetPDGeomIDVec() { return m_PDGeomIDVec; }
    double GetLrefSigFig(); // For display precision purposes

    // Update Methods
    void Update();
    void UpdateWettedAreaTotals();
    void UpdateRefWing();
    void UpdateAltLimits();
    void UpdateTempLimits();
    void UpdateParmActivity();

    // General Methods
    void ClearInputVectors();
    void ClearOutputVectors();

    // Miscellaneous Methods
    void DeactivateParms();
    bool IsSameGeomSet();
    bool IsNotZeroLineItem(int index);
    void RefreshDegenGeom();

    // Reference Qualities Parms
    Parm m_Sref;
    string m_RefGeomID;
    IntParm m_RefFlag;

    // Options Parms
    IntParm m_VinfUnitType;
    IntParm m_AltLengthUnit;
    IntParm m_SetChoice;
    IntParm m_LengthUnit;
    IntParm m_TempUnit;
    IntParm m_PresUnit;

    // Air Qualities Parms
    Parm m_Vinf;
    Parm m_Hinf;
    Parm m_Temp;
    Parm m_Mach;

private:
    ParasiteDragMgrSingleton();

    vector < ParasiteDragTableRow > m_TableRowVec;
    ParasiteDragTableRow m_DefaultStruct;

    // Main Table Geom Related Vectors
    vector <string> m_PDGeomIDVec;
    vector <DegenGeom> m_DegenGeomVec;
    Results* m_CompGeomResults;

    // Miscellaneous Variables
    int m_RowSize;              // Number of rows for main table

    // Main Build Up Table Variables
    vector <string> geo_geomID;
    vector <string> geo_subsurfID;
    vector <string> geo_label;
    vector < int > geo_surfNum;
    vector <double> geo_swet;
    vector <double> geo_lref;
    vector <double> geo_fineRat;
    vector <int> geo_shapeType;
};

#define ParasiteDragMgr ParasiteDragMgrSingleton::getInstance()

#endif