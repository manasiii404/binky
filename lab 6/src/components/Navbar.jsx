import { Link, useLocation, useNavigate } from 'react-router-dom'
import { useAuth } from '../context/AuthContext'
import './Navbar.css'

function Navbar() {
    const location = useLocation()
    const navigate = useNavigate()
    const { user, logout } = useAuth()

    const isActive = (path) => location.pathname === path

    const handleLogout = () => {
        logout()
        navigate('/login')
    }

    return (
        <nav className="navbar glass">
            <div className="nav-container">
                <Link to="/" className="nav-logo">
                    <span className="logo-icon">📚</span>
                    <span className="logo-text">BookStore</span>
                </Link>

                <ul className="nav-menu">
                    <li className="nav-item">
                        <Link
                            to="/"
                            className={`nav-link ${isActive('/') ? 'active' : ''}`}
                        >
                            Home
                        </Link>
                    </li>
                    <li className="nav-item">
                        <Link
                            to="/catalogue"
                            className={`nav-link ${isActive('/catalogue') ? 'active' : ''}`}
                        >
                            Catalogue
                        </Link>
                    </li>

                    {user ? (
                        <>
                            <li className="nav-item">
                                <span className="nav-user">Hi, {user.fullName}</span>
                            </li>
                            <li className="nav-item">
                                <button onClick={handleLogout} className="btn btn-secondary btn-sm">
                                    Logout
                                </button>
                            </li>
                        </>
                    ) : (
                        <>
                            <li className="nav-item">
                                <Link
                                    to="/login"
                                    className={`nav-link ${isActive('/login') ? 'active' : ''}`}
                                >
                                    Login
                                </Link>
                            </li>
                            <li className="nav-item">
                                <Link
                                    to="/register"
                                    className="btn btn-primary"
                                >
                                    Sign Up
                                </Link>
                            </li>
                        </>
                    )}
                </ul>
            </div>
        </nav>
    )
}

export default Navbar
