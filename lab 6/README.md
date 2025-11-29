# Glassmorphic Online Bookstore

A stunning, responsive online bookstore built with React featuring a beautiful glassmorphic design with animated gradients and modern UI/UX.

## Features

- ✨ **Glassmorphic Design**: Beautiful frosted glass effect with backdrop blur
- 🎨 **Animated Gradients**: Dynamic background with floating particles
- 📱 **Fully Responsive**: Works perfectly on desktop, tablet, and mobile
- 🔐 **Authentication Pages**: Login and Registration with form validation
- 📚 **Book Catalogue**: Browse books with search and category filtering
- 🎯 **Modern UI/UX**: Smooth animations and hover effects
- ⚡ **Fast Performance**: Built with Vite for lightning-fast development

## Pages

1. **Home** - Hero section with features showcase
2. **Login** - User authentication with social login options
3. **Register** - New user registration with validation
4. **Catalogue** - Browse and search books with filters

## Tech Stack

- **React 18** - UI library
- **Vite** - Build tool and dev server
- **React Router** - Client-side routing
- **CSS3** - Glassmorphism and animations
- **Google Fonts (Poppins)** - Modern typography

## Installation

1. Navigate to the project directory:
```bash
cd "c:\VIT\Sem 5\CN\lab exam\lab 6a"
```

2. Install dependencies:
```bash
npm install
```

3. Start the development server:
```bash
npm run dev
```

4. Open your browser and visit: `http://localhost:5173`

## Build for Production

```bash
npm run build
```

The optimized production build will be in the `dist` folder.

## Preview Production Build

```bash
npm run preview
```

## Project Structure

```
lab 6a/
├── src/
│   ├── components/
│   │   ├── Navbar.jsx
│   │   └── Navbar.css
│   ├── pages/
│   │   ├── Home.jsx
│   │   ├── Home.css
│   │   ├── Login.jsx
│   │   ├── Login.css
│   │   ├── Register.jsx
│   │   ├── Register.css
│   │   ├── Catalogue.jsx
│   │   └── Catalogue.css
│   ├── App.jsx
│   ├── App.css
│   ├── main.jsx
│   └── index.css
├── index.html
├── package.json
└── vite.config.js
```

## Design Features

### Glassmorphism
- Frosted glass effect with `backdrop-filter: blur()`
- Semi-transparent backgrounds
- Subtle borders and shadows
- Smooth hover transitions

### Color Palette
- Primary: Purple gradient (#667eea → #764ba2)
- Secondary: Pink gradient (#f093fb → #f5576c)
- Accent: Blue gradient (#4facfe → #00f2fe)
- Background: Multi-color gradient with animated particles

### Typography
- Font Family: Poppins (Google Fonts)
- Weights: 300, 400, 500, 600, 700

## Responsive Breakpoints

- Desktop: > 768px
- Mobile: ≤ 768px

## Browser Support

- Chrome (latest)
- Firefox (latest)
- Safari (latest)
- Edge (latest)

## Features Showcase

### Home Page
- Eye-catching hero section
- Feature cards with icons
- Call-to-action buttons
- Smooth scroll animations

### Catalogue Page
- 8 sample books with details
- Real-time search functionality
- Category filtering
- Responsive grid layout
- Book ratings and pricing

### Authentication
- Login with email/password
- Social login buttons (Google, Facebook)
- Registration with validation
- Password confirmation
- Terms & conditions checkbox

## Customization

### Change Colors
Edit the CSS variables in `src/index.css`:
```css
:root {
  --primary-gradient: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
  --secondary-gradient: linear-gradient(135deg, #f093fb 0%, #f5576c 100%);
  /* ... */
}
```

### Add More Books
Edit the `booksData` array in `src/pages/Catalogue.jsx`

## License

This is an educational project for learning React and modern web design.

## Credits

Created as part of Computer Networks lab coursework demonstrating modern web development with React.
