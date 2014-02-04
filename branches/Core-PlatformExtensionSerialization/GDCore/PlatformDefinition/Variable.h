/** \file
 *  Game Develop
 *  2008-2014 Florian Rival (Florian.Rival@gmail.com)
 */

#ifndef GDCORE_VARIABLE_H
#define GDCORE_VARIABLE_H
#include <string>
#include <map>
class TiXmlElement;

namespace gd
{

/**
 * \brief Defines a variable which can be used by an object, a layout or a project.
 *
 * \see gd::VariablesContainer
 *
 * \ingroup PlatformDefinition
 */
class GD_CORE_API Variable
{
public:

    /**
     * \brief Default constructor creating a variable with 0 as value.
     */
    Variable() : value(0), isNumber(true), isStructure(false) {};
    virtual ~Variable() {};

    /** \name Number or string
     * Methods and operators used when the variable is considered as a number or a string.
     */
    ///@{

    /**
     * \brief Return the content of the variable, considered as a string.
     */
    const std::string & GetString() const;

    /**
     * \brief Change the content of the variable, considered as a string.
     */
    virtual void SetString(const std::string & newStr)
    {
        str = newStr;
        isNumber = false;
        isStructure = false;
    }

    /**
     * \brief Return the content of the variable, considered as a number.
     */
    double GetValue() const;

    /**
     * \brief Change the content of the variable, considered as a number.
     */
    virtual void SetValue(double val)
    {
        value = val;
        isNumber = true;
        isStructure = false;
    }

    //Operators are overloaded to allow accessing to variable using a simple int-like semantic.
    void operator=(double val)  {SetValue(val);};
    void operator+=(double val) {SetValue(val+GetValue());}
    void operator-=(double val) {SetValue(GetValue()-val);}
    void operator*=(double val) {SetValue(val*GetValue());}
    void operator/=(double val) {SetValue(GetValue()/val);}

    bool operator<=(double val) const { return GetValue() <= val;};
    bool operator>=(double val) const { return GetValue() >= val;};
    bool operator<(double val) const { return GetValue() < val;};
    bool operator>(double val) const { return GetValue() > val;};
    bool operator==(double val) const { return GetValue() == val;};
    bool operator!=(double val) const { return GetValue() != val;};

    //Operators are overloaded to allow accessing to variable using a simple string-like semantic.
    void operator=(const std::string & val)  {SetString(val);};
    void operator+=(const std::string & val) {SetString(GetString()+val);}

    bool operator==(const std::string & val) const { return GetString() == val;};
    bool operator!=(const std::string & val) const { return GetString() != val;};

    /** 
     * \brief Return true if the variable is a number
     */
    bool IsNumber() const { return !isStructure && isNumber; }
    ///@}

    /** \name Structure
     * Methods used when the variable is considered as a structure.
     */
    ///@{

    /**
     * \brief Return true if the variable is a structure which can have children.
     */
    bool IsStructure() const { return isStructure; }

    /**
     * \brief Return true if the variable is a structure and has the specified child.
     */
    virtual bool HasChild(const std::string & name) const;

    /**
     * \brief Return the child with the specified name. 
     * 
     * If the variable has not the specified child, an empty variable with the specified name 
     * is added as child.
     */
    virtual Variable & GetChild(const std::string & name);

    /**
     * \brief Return the child with the specified name. 
     * 
     * If the variable has not the specified child, an empty variable with the specified name 
     * is added as child.
     */
    virtual const Variable & GetChild(const std::string & name) const;

    /**
     * \brief Remove the child with the specified name.
     * 
     * If the variable is not a structure or has not
     * the specified child, nothing is done.
     */
    void RemoveChild(const std::string & name);

    /**
     * \brief Get the map containing all the children.
     */
    const std::map<std::string, Variable> & GetAllChildren() const { return children; }

    ///@}

    /** \name Serialization
     * Methods used when to load or save a variable to XML.
     */
    ///@{
    /**
     * Called to save the layout to a TiXmlElement.
     */
    void SaveToXml(TiXmlElement * element) const;

    /**
     * Called to load the layout from a TiXmlElement.
     */
    void LoadFromXml(const TiXmlElement * element);
    ///@}


private:
    mutable double value;
    mutable std::string str;
    mutable bool isNumber; ///< True if the type of the variable is a number.
    mutable bool isStructure; ///< False when the variable is a primitive ( i.e: Number or string ), true when it is a structure and has may have children.
    mutable std::map<std::string, Variable> children; ///<Children, when the variable is considered as a structure.
};

}

#endif // GDCORE_VARIABLE_H