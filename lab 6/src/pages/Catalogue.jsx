import { useState, useEffect } from 'react'
import { useAuth } from '../context/AuthContext'
import './Catalogue.css'

function Catalogue() {
    const [books, setBooks] = useState([])
    const [searchTerm, setSearchTerm] = useState('')
    const [selectedCategory, setSelectedCategory] = useState('All')
    const { user } = useAuth()
    const [showAddModal, setShowAddModal] = useState(false)
    const [newBook, setNewBook] = useState({
        title: '',
        author: '',
        price: '',
        category: ''
    })

    useEffect(() => {
        fetchBooks()
    }, [])

    const fetchBooks = () => {
        fetch('http://localhost:5000/api/books')
            .then(res => res.json())
            .then(data => setBooks(data))
            .catch(err => console.error('Error fetching books:', err))
    }

    const handleAddBook = (e) => {
        e.preventDefault()

        fetch('http://localhost:5000/api/books', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({
                ...newBook,
                sellerId: user.id
            })
        })
            .then(res => res.json())
            .then(data => {
                alert('Book added successfully!')
                setShowAddModal(false)
                setNewBook({ title: '', author: '', price: '', category: '' })
                fetchBooks()
            })
            .catch(err => alert('Failed to add book'))
    }

    const categories = ['All', ...new Set(books.map(book => book.category))]

    const filteredBooks = books.filter(book => {
        const matchesSearch = book.title.toLowerCase().includes(searchTerm.toLowerCase()) ||
            book.author.toLowerCase().includes(searchTerm.toLowerCase())
        const matchesCategory = selectedCategory === 'All' || book.category === selectedCategory
        return matchesSearch && matchesCategory
    })

    return (
        <div className="catalogue-page">
            <div className="catalogue-container">
                <div className="catalogue-header">
                    <h1 className="catalogue-title">Book Catalogue</h1>
                    <p className="catalogue-subtitle">Discover your next favorite book</p>

                    {user && user.role === 'seller' && (
                        <button
                            className="btn btn-primary add-book-btn"
                            onClick={() => setShowAddModal(true)}
                        >
                            + Add New Book
                        </button>
                    )}
                </div>

                {showAddModal && (
                    <div className="modal-overlay">
                        <div className="modal-content glass-card">
                            <h2>Add New Book</h2>
                            <form onSubmit={handleAddBook}>
                                <div className="input-group">
                                    <input
                                        type="text"
                                        placeholder="Book Title"
                                        value={newBook.title}
                                        onChange={e => setNewBook({ ...newBook, title: e.target.value })}
                                        required
                                    />
                                </div>
                                <div className="input-group">
                                    <input
                                        type="text"
                                        placeholder="Author"
                                        value={newBook.author}
                                        onChange={e => setNewBook({ ...newBook, author: e.target.value })}
                                        required
                                    />
                                </div>
                                <div className="input-group">
                                    <input
                                        type="number"
                                        placeholder="Price"
                                        value={newBook.price}
                                        onChange={e => setNewBook({ ...newBook, price: e.target.value })}
                                        required
                                    />
                                </div>
                                <div className="input-group">
                                    <input
                                        type="text"
                                        placeholder="Category"
                                        value={newBook.category}
                                        onChange={e => setNewBook({ ...newBook, category: e.target.value })}
                                        required
                                    />
                                </div>
                                <div className="modal-actions">
                                    <button type="submit" className="btn btn-primary">Add Book</button>
                                    <button
                                        type="button"
                                        className="btn btn-secondary"
                                        onClick={() => setShowAddModal(false)}
                                    >
                                        Cancel
                                    </button>
                                </div>
                            </form>
                        </div>
                    </div>
                )}

                <div className="catalogue-filters glass-card">
                    <div className="search-box">
                        <input
                            type="text"
                            placeholder="Search books or authors..."
                            value={searchTerm}
                            onChange={(e) => setSearchTerm(e.target.value)}
                            className="search-input"
                        />
                    </div>

                    <div className="category-filters">
                        {categories.map(category => (
                            <button
                                key={category}
                                className={`category-btn ${selectedCategory === category ? 'active' : ''}`}
                                onClick={() => setSelectedCategory(category)}
                            >
                                {category}
                            </button>
                        ))}
                    </div>
                </div>

                <div className="books-grid">
                    {filteredBooks.map(book => (
                        <div key={book._id} className="book-card glass-card">
                            <div className="book-cover">{book.cover || '📘'}</div>
                            <div className="book-info">
                                <h3 className="book-title">{book.title}</h3>
                                <p className="book-author">by {book.author}</p>
                                <div className="book-meta">
                                    <span className="book-category">{book.category}</span>
                                    <span className="book-rating">⭐ {book.rating || 'New'}</span>
                                </div>
                                <div className="book-footer">
                                    <span className="book-price">Rs. {book.price}</span>
                                    <button className="btn btn-primary btn-small">Add to Cart</button>
                                </div>
                            </div>
                        </div>
                    ))}
                </div>

                {filteredBooks.length === 0 && (
                    <div className="no-results glass-card">
                        <p>No books found matching your criteria</p>
                    </div>
                )}
            </div>
        </div>
    )
}

export default Catalogue
