/** \file
 *  Game Develop
 *  2008-2014 Florian Rival (Florian.Rival@gmail.com)
 */
#ifndef GDCORE_CLASSWITHOBJECTS_H
#define GDCORE_CLASSWITHOBJECTS_H
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
namespace gd { class Object; }
namespace gd { class Project; }
class TiXmlElement;
#undef GetObject //Disable an annoying macro

namespace gd
{

/**
 * \brief Used as a base class for classes that will own objects (see gd::Object).
 *
 * For example, gd::Project inherits from this class as it have global objects.<br>
 * gd::Layout also inherits from this class as each layout has specific objects.
 *
 * \see gd::Project
 * \see gd::Layout
 * \see gd::Object
 *
 * \ingroup PlatformDefinition
 */
class GD_CORE_API ClassWithObjects
{
public:
    /**
     * \brief Default constructor creating a container without any objects.
     */
    ClassWithObjects();
    virtual ~ClassWithObjects() {};

    /** \name Objects management
     * Members functions related to objects management.
     */
    ///@{

    /**
     * \brief Return true if object called \a name exists.
     */
    bool HasObjectNamed(const std::string & name) const;

    /**
     * \brief Return a reference to the object called \a name.
     */
    Object & GetObject(const std::string & name);

    /**
     * \brief Return a reference to the object called \a name.
     */
    const gd::Object & GetObject(const std::string & name) const;

    /**
     * \brief Return a reference to the object at position \a index in the objects list
     */
    Object & GetObject(unsigned int index);

    /**
     * \brief Return a reference to the object at position \a index in the objects list.
     */
    const gd::Object & GetObject (unsigned int index) const;

    /**
     * \brief Return the position of the object called \a name in the objects list.
     *
     * \warning This has nothing to do with an object position on a layout. Objects put on layouts
     * are represented thanks to the gd::InitialInstance class.
     */
    unsigned int GetObjectPosition(const std::string & name) const;

    /**
     * \brief Return the number of object.
     */
    unsigned int GetObjectsCount() const;

#if defined(GD_IDE_ONLY)
    /**
     * \brief Add a new empty object of type \a objectType called \a name at the specified position in the layout list.<br>
     *
     * \note The object is created using the project's current platform.
     */
    void InsertNewObject(gd::Project & project, const std::string & objectType, const std::string & name, unsigned int position);
#endif

    /**
     * \brief Must add a new object constructed from the layout passed as parameter.
     * \note No pointer or reference must be kept on the object passed as parameter.
     * \param object The object that must be copied and inserted into the project
     * \param position Insertion position. If the position is invalid, the object is inserted at the end of the objects list.
     */
    void InsertObject(const gd::Object & object, unsigned int position);

    /**
     * \brief Delete an object.
     * \param name The name of the object to be deleted.
     */
    void RemoveObject(const std::string & name);

    /**
     * \brief Swap the position of the specified objects.
     */
    void SwapObjects(unsigned int firstObjectIndex, unsigned int secondObjectIndex);

    /**
     * Provide a raw access to the vector containing the objects
     */
    std::vector < boost::shared_ptr<gd::Object> > & GetObjects() { return initialObjects; }

    /**
     * Provide a raw access to the vector containing the objects
     */
    const std::vector < boost::shared_ptr<gd::Object> > & GetObjects() const  { return initialObjects; }
    ///@}

    /** \name Saving and loading
     * Members functions related to saving and loading the project.
     */
    ///@{
    /**
     * \brief Save the objects to xml
     */
    void SaveObjectsToXml(TiXmlElement * element) const;

    /**
     * \brief Load the objects from xml
     */
    void LoadObjectsFromXml(gd::Project & project, const TiXmlElement * element);
    ///@}

protected:
    std::vector < boost::shared_ptr<gd::Object> > initialObjects; ///< Objects contained.
};

}

#endif // GDCORE_CLASSWITHOBJECTS_H