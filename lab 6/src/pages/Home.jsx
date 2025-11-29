import { Link } from 'react-router-dom'
import './Home.css'

function Home() {
    return (
        <div className="home">
            <div className="hero-section">
                <div className="hero-content glass-card">
                    <h1 className="hero-title">
                        Welcome to the
                        <span className="gradient-text"> Glassmorphic Bookstore</span>
                    </h1>
                    <p className="hero-subtitle">
                        Discover your next favorite book in our stunning collection
                    </p>
                    <div className="hero-buttons">
                        <Link to="/catalogue" className="btn btn-primary">
                            Browse Catalogue
                        </Link>
                        <Link to="/register" className="btn btn-secondary">
                            Get Started
                        </Link>
                    </div>
                </div>
            </div>

            <div className="features-section">
                <div className="container">
                    <h2 className="section-title">Why Choose Us?</h2>
                    <div className="features-grid">
                        <div className="feature-card glass-card">
                            <div className="feature-icon">📖</div>
                            <h3>Vast Collection</h3>
                            <p>Thousands of books across all genres and categories</p>
                        </div>
                        <div className="feature-card glass-card">
                            <div className="feature-icon">⚡</div>
                            <h3>Fast Delivery</h3>
                            <p>Get your books delivered within 2-3 business days</p>
                        </div>
                        <div className="feature-card glass-card">
                            <div className="feature-icon">💎</div>
                            <h3>Premium Quality</h3>
                            <p>Only the best editions and printing quality</p>
                        </div>
                        <div className="feature-card glass-card">
                            <div className="feature-icon">🎁</div>
                            <h3>Special Offers</h3>
                            <p>Exclusive deals and discounts for members</p>
                        </div>
                    </div>
                </div>
            </div>

            <div className="cta-section">
                <div className="cta-content glass-card">
                    <h2>Ready to Start Reading?</h2>
                    <p>Join thousands of book lovers today</p>
                    <Link to="/register" className="btn btn-primary">
                        Create Account
                    </Link>
                </div>
            </div>
        </div>
    )
}

export default Home
