#ifndef BOOTSTRAP_HPP
#    define BOOTSTRAP_HPP

static_assert(__clang__ && __cplusplus >= 199711L, "Your compiler is not supported.");

#    include <cstdint>
#    include <map>

#    include "Platform.hpp" // Contains platform-specific junk

namespace detail
{

    /**
     * The ultimate base class for all bootstrap implementations.
     * 
     * Internally used, this class allows for heterogenus storage of bootstrap implementations in STL containers 
     * while at the same time providing a simple means by which to tell whether glew has been initialized or not
     * 
     */
    struct AbstractBootstrap
    {
      protected:

        /// Has glew been initialized yet?
        static thread_local bool glew_initialized;

      public:

        /**
         * Implicitly invoked at the end of bootstrap construction
         * 
         */
        virtual void init() = 0;

        /**
         * Implicitly invoked by GLUT
         * 
         * @param width the new width of the application window
         * 
         * @param height the new height of the application window
         * 
         * @TODO: SEE
         */
        virtual void reshape(std::size_t width, std::size_t height) = 0;

        /**
         * Implicitly invoked by GLUT
         * 
         * @see (https://www.opengl.org/resources/libraries/glut/spec3/node63.html)
         * 
         */
        virtual void idle() = 0;

        /**
         * Implicitly invoked by GLUT
         * 
         * @see (http://www.opengl.org/resources/libraries/glut/spec3/node46.html)
         * 
         */
        virtual void render() = 0;

        /**
         * Implicitly invoked by GLUT
         * 
         * @TODO SEE
         * 
         */
        virtual void keyboard(unsigned char key, int x, int y) = 0;
        
        virtual void mouse(int button, int state,
                                int x, int y) = 0;
        
        virtual void activeMotion(int x, int y) = 0;
        virtual void passiveMotion(int x, int y) = 0;

        /**
         * Default virtual destructor
         * 
         */
        virtual ~AbstractBootstrap() = default;
    };

    thread_local bool AbstractBootstrap::glew_initialized = false;

    /// A pointer to the currently active bootstrap
    thread_local AbstractBootstrap* current = nullptr;

    /// A mapping of all valid bootstraps
    thread_local std::map<int, AbstractBootstrap*> bootstraps;

    /**
     * Registers the provided bootstrap
     * 
     * @tparam N the ID of the bootstrap to register
     * 
     * @param bootstrap the bootstrap to register
     * 
     */
    template<int N>
    void register_this(AbstractBootstrap* bootstrap) noexcept
    {
        bootstraps.insert(std::make_pair(N, bootstrap));
    }

    /**
     * Unregisters 'this' bootstrap
     * 
     * @tparam N the ID of the bootstrap to unregister
     * 
     */
    template<int N>
    void unregister_this() noexcept
    {
        bootstraps.erase(N);
    }

    /**
     * A delegate function that is compatible with GLUT that acts as a bridge between the C and C++ APIs
     * 
     * @tparam N the ID of the bootstrap that this delegate represents
     * 
     */
    template<int N>
    void glutIdleFuncDelegate()
    {
        bootstraps[N]->idle();
    }

    /**
     * A delegate function that is compatible with GLUT that acts as a bridge between the C and C++ APIs
     * 
     * @tparam N the ID of the bootstrap that this delegate represents
     * 
     */
    template<int N>
    void glutDisplayFuncDelegate()
    {
        /// HACK! Switch out the idle function delegate if the active window has changed
        if(bootstraps[N] != current)
        {
            /// Invoke new idle function one time
            glutIdleFuncDelegate<N>();
            /// Set subsequent idle function invocations
            glutIdleFunc(glutIdleFuncDelegate<N>);
            current = bootstraps[N];
        }
        bootstraps[N]->render();
    }

    template<int N>
    void glutReshapeFuncDelegate(int width, int height)
    {
        bootstraps[N]->reshape(static_cast<std::size_t>(width), static_cast<std::size_t>(height));
    }

    template<int N>
    void glutKeystrokeDelegate(unsigned char key, int x, int y)
    {
        bootstraps[N]->keyboard(key, x, y);
    }
    
    template<int N>
    void glutMouseFuncDelegate(int button, int state,
                                int x, int y)
    {
        bootstraps[N]->mouse(button, state, x, y);
    }
    
    template<int N>   
    void glutMotionFuncDelegate(int x, int y)
    {
        bootstraps[N]->activeMotion(x, y);
    }
    
    template<int N>
    void glutPassiveMotionFunc(int x, int y)
    {
        bootstraps[N]->passiveMotion(x, y);
    }
}

/**
 * The default bootstrap implementation.  A bootstrap encapsulates the underlying C-API that provides native GUI 
 * resources.
 * 
 * TODO: Docs @ options ( + defaults )
 * 
 * Derived classes are expected to override the appropriate virtual methods.
 * 
 * @tparam N the static ID of this bootstrap
 * 
 */
template<int N>
class Bootstrap : public detail::AbstractBootstrap
{
  public:

    Bootstrap(int windowWidth, int windowHeight)
    {
        glutInitWindowSize(windowWidth, windowHeight);
        glutInitWindowPosition(100, 100);
        glutCreateWindow((std::string("Bootstrap Test (") + std::to_string(N) + ")").c_str());
        if(!glew_initialized)
        {
            glewInit();
            glew_initialized = true;
        }
        glutDisplayFunc(detail::glutDisplayFuncDelegate<N>);
        glutIdleFunc(detail::glutIdleFuncDelegate<N>);
        glutReshapeFunc(detail::glutReshapeFuncDelegate<N>);
        glutKeyboardFunc(detail::glutKeystrokeDelegate<N>);
        glutMouseFunc(detail::glutMouseFuncDelegate<N>);
        ::glutMotionFunc(detail::glutMotionFuncDelegate<N>);
        detail::register_this<N>(this);
    }

    virtual void init()
    {
    }

    virtual void reshape(std::size_t, std::size_t)
    {
    }

    virtual void idle()
    {
    }

    virtual void render()
    {
    }

    virtual void keyboard(unsigned char, int, int)
    {
    }

    virtual void mouse(int, int,
                                int, int)
    {
        
    }
    
    virtual void activeMotion(int, int)
    {
        
    }
    
    virtual void passiveMotion(int, int)
    {
        
    }
    
    virtual ~Bootstrap()
    {
        detail::unregister_this<N>();
    }
};

#endif